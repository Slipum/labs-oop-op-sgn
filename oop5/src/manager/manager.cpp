#include "manager.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>

#include "logger.h"
#include "entrypoint/entrypoint.h"

ElevatorManager::ElevatorManager(std::unique_ptr<Elevator> elevator) : _elevator(std::move(elevator)) {}

void ElevatorManager::setTimerHost(ElevatorTimerHost host) {
    _timers = std::move(host);
}

void ElevatorManager::setStateChangedCallback(StateChangedCallback callback) {
    _onStateChanged = std::move(callback);
}

Elevator &ElevatorManager::elevator() {
    return *_elevator;
}

const Elevator &ElevatorManager::elevator() const {
    return *_elevator;
}

void ElevatorManager::notifyStateChanged() {
    if (_onStateChanged) {
        _onStateChanged();
    }
}

void ElevatorManager::callFromFloor(int floor) {
    if (!_elevator->controller().isValidFloor(floor)) {
        Logger::instance().error((std::ostringstream() << "Некорректный вызов с этажа: " << floor).str());
        return;
    }
    enqueueFloor(floor, "этаж");
}

void ElevatorManager::callFromCabin(int floor) {
    if (!_elevator->controller().isValidFloor(floor)) {
        Logger::instance().error((std::ostringstream() << "Некорректная команда из кабины: " << floor).str());
        return;
    }
    enqueueFloor(floor, "кабина");
}

void ElevatorManager::enqueueFloor(int floor, const char *source) {
    auto &ctrl = _elevator->controller();
    Logger::instance().log((std::ostringstream() << "Вызов лифта (" << source << ") на этаж " << floor).str());

    if (!ctrl.hasPendingFloor(floor)) {
        ctrl.addPendingFloor(floor);
        notifyStateChanged();
    }

    const bool hasOtherTargets =
        std::any_of(ctrl.pendingFloors().cbegin(), ctrl.pendingFloors().cend(),
                    [&ctrl](int pendingFloor) { return pendingFloor != ctrl.currentFloor(); });

    if (ctrl.state() == ControllerState::Free && _elevator->door().state() == DoorState::Closed &&
        ctrl.currentFloor() == floor && !hasOtherTargets) {
        arriveAtFloor();
        return;
    }

    if (ctrl.state() == ControllerState::Moving) {
        pickNextTarget();
        Logger::instance().log((std::ostringstream() << "Новая цель: этаж " << ctrl.targetFloor()).str());
        notifyStateChanged();
        if (_timers.startMoveTimer) {
            continueMoving();
        }
        return;
    }

    if (ctrl.state() == ControllerState::ReachingTarget) {
        return;
    }

    schedule();
}

void ElevatorManager::schedule() {
    auto &ctrl = _elevator->controller();
    if (ctrl.pendingFloors().empty() || ctrl.state() != ControllerState::Free) {
        return;
    }
    pickNextTarget();
    startMoving();
}

void ElevatorManager::pickNextTarget() {
    auto &ctrl = _elevator->controller();
    if (ctrl.pendingFloors().empty()) {
        ctrl.setTargetFloor(ctrl.currentFloor());
        ctrl.setDirection(MoveDirection::Idle);
        return;
    }

    if (ctrl.direction() == MoveDirection::Idle) {
        int bestFloor = ctrl.currentFloor();
        int bestDistance = INT_MAX;
        for (int floor : ctrl.pendingFloors()) {
            if (floor == ctrl.currentFloor()) {
                continue;
            }
            const int distance = abs(floor - ctrl.currentFloor());
            if (distance < bestDistance) {
                bestDistance = distance;
                bestFloor = floor;
            }
        }
        if (bestDistance == INT_MAX) {
            bestFloor = ctrl.currentFloor();
        }
        ctrl.setTargetFloor(bestFloor);
        ctrl.setDirection(ctrl.targetFloor() > ctrl.currentFloor()
            ? MoveDirection::Up
            : ctrl.targetFloor() < ctrl.currentFloor() ? MoveDirection::Down
            : MoveDirection::Idle);
        return;
    }

    if (ctrl.direction() == MoveDirection::Up) {
        int nextUp = INT_MAX;
        for (int floor : ctrl.pendingFloors()) {
            if (floor >= ctrl.currentFloor() && floor < nextUp) {
                nextUp = floor;
            }
        }
        if (nextUp != INT_MAX) {
            ctrl.setTargetFloor(nextUp);
            return;
        }
        ctrl.setDirection(MoveDirection::Down);
        pickNextTarget();
        return;
    }

    int nextDown = -1;
    for (int floor : ctrl.pendingFloors()) {
        if (floor <= ctrl.currentFloor() && floor > nextDown) {
            nextDown = floor;
        }
    }
    if (nextDown != -1) {
        ctrl.setTargetFloor(nextDown);
        return;
    }
    ctrl.setDirection(MoveDirection::Up);
    pickNextTarget();
}

void ElevatorManager::startMoving() {
    auto &ctrl = _elevator->controller();
    if (ctrl.currentFloor() == ctrl.targetFloor() && ctrl.hasPendingFloor(ctrl.currentFloor())) {
        arriveAtFloor();
        return;
    }

    if (_elevator->door().state() != DoorState::Closed) {
        Logger::instance().error("Движение отложено: двери не закрыты");
        return;
    }

    if (ctrl.currentFloor() == ctrl.targetFloor()) {
        return;
    }

    _elevator->cabin().block();
    _elevator->cabin().prepareToMove();

    ctrl.setState(ControllerState::Moving);
    Logger::instance().log((std::ostringstream() << "Начало движения к этажу " << ctrl.targetFloor()).str());
    notifyStateChanged();

    _elevator->cabin().startMoving();
    continueMoving();
}

void ElevatorManager::continueMoving() {
    auto &ctrl = _elevator->controller();
    if (ctrl.state() != ControllerState::Moving || !_timers.startMoveTimer) {
        return;
    }
    _elevator->cabin().startMoving();
    _timers.startMoveTimer(ElevatorConfig::WAIT_MS);
}

void ElevatorManager::onMove() {
    auto &ctrl = _elevator->controller();
    if (ctrl.state() != ControllerState::Moving) {
        Logger::instance().error("Таймер движения проигнорирован");
        return;
    }

    if (ctrl.currentFloor() < ctrl.targetFloor()) {
        ctrl.stepUp();
    } else if (ctrl.currentFloor() > ctrl.targetFloor()) {
        ctrl.stepDown();
    }

    Logger::instance().log((std::ostringstream() << "Текущий этаж: " << ctrl.currentFloor()).str());
    notifyStateChanged();

    if (ctrl.hasPendingFloor(ctrl.currentFloor())) {
        arriveAtFloor();
        return;
    }

    if (ctrl.currentFloor() == ctrl.targetFloor()) {
        pickNextTarget();
        if (ctrl.targetFloor() != ctrl.currentFloor()) {
            Logger::instance().log((std::ostringstream() << "Промежуточная смена цели: этаж " << ctrl.targetFloor()).str());
            notifyStateChanged();
        }
    }

    if (ctrl.currentFloor() != ctrl.targetFloor()) {
        continueMoving();
        return;
    }

    if (!ctrl.pendingFloors().empty()) {
        pickNextTarget();
        if (ctrl.currentFloor() != ctrl.targetFloor()) {
            Logger::instance().log((std::ostringstream() << "Смена цели без остановки: этаж " << ctrl.targetFloor()).str());
            notifyStateChanged();
            continueMoving();
            return;
        }
    }

    ctrl.setState(ControllerState::Free);
    _elevator->cabin().stop();
    ctrl.setDirection(MoveDirection::Idle);
    notifyStateChanged();
}

void ElevatorManager::arriveAtFloor() {
    auto &ctrl = _elevator->controller();
    if (_timers.stopMoveTimer) {
        _timers.stopMoveTimer();
    }
    ctrl.setState(ControllerState::ReachingTarget);
    _elevator->cabin().stop();

    Logger::instance().log((std::ostringstream() << "Прибытие на этаж " << ctrl.currentFloor()).str());
    notifyStateChanged();

    beginDoorCycle();
}

void ElevatorManager::beginDoorCycle() {
    _elevator->cabin().unblock();
    _elevator->door().open();
    if (_timers.startDoorOpenTimer) {
        _timers.startDoorOpenTimer(ElevatorConfig::DOOR_OPEN_MS);
    }
}

void ElevatorManager::onDoorOpen() {
    _elevator->door().completeOpen();
    if (_timers.startWaitTimer) {
        _timers.startWaitTimer(ElevatorConfig::FLOOR_WAIT_MS);
    }
}

void ElevatorManager::onWait() {
    _elevator->door().close();
    if (_timers.startDoorCloseTimer) {
        _timers.startDoorCloseTimer(ElevatorConfig::DOOR_CLOSE_MS);
    }
}

void ElevatorManager::onDoorClose() {
    _elevator->door().completeClose();
    finishStopAtFloor();
}

void ElevatorManager::finishStopAtFloor() {
    auto &ctrl = _elevator->controller();
    ctrl.removePendingFloor(ctrl.currentFloor());
    _elevator->cabin().block();
    ctrl.setState(ControllerState::Free);

    if (ctrl.pendingFloors().empty()) {
        ctrl.setDirection(MoveDirection::Idle);
        Logger::instance().log("Очередь заявок пуста");
        notifyStateChanged();
        return;
    }

    pickNextTarget();

    Logger::instance().log((std::ostringstream() << "Следующая цель: этаж " << ctrl.targetFloor()).str());
    notifyStateChanged();

    schedule();
}
