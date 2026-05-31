#include "manager.h"

#include <algorithm>
#include <climits>
#include <iostream>

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
        std::cerr << "[Менеджер] Некорректный вызов с этажа: " << floor << std::endl;
        return;
    }
    enqueueFloor(floor, "этаж");
}

void ElevatorManager::callFromCabin(int floor) {
    if (!_elevator->controller().isValidFloor(floor)) {
        std::cerr << "[Менеджер] Некорректная команда из кабины: " << floor << std::endl;
        return;
    }
    enqueueFloor(floor, "кабина");
}

void ElevatorManager::enqueueFloor(int floor, const char *source) {
    auto &ctrl = _elevator->controller();
    std::cout << "[Менеджер] Вызов лифта (" << source << ") на этаж " << floor << std::endl;

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
        std::cout << "[Менеджер] Новая цель: этаж " << ctrl.targetFloor() << ", направление: "
                  << ctrl.directionName() << std::endl;
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
        std::cerr << "[Менеджер] Движение отложено: двери не закрыты" << std::endl;
        return;
    }

    if (ctrl.currentFloor() == ctrl.targetFloor()) {
        return;
    }

    _elevator->cabin().block();
    _elevator->cabin().prepareToMove();

    ctrl.setState(ControllerState::Moving);
    std::cout << "[Менеджер] Начало движения к этажу " << ctrl.targetFloor() << " ("
              << ctrl.directionName() << ")" << std::endl;
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

void ElevatorManager::onMoveTimerElapsed() {
    auto &ctrl = _elevator->controller();
    if (ctrl.state() != ControllerState::Moving) {
        std::cerr << "[Менеджер] Таймер движения проигнорирован, состояние: " << ctrl.stateName()
                  << std::endl;
        return;
    }

    if (ctrl.currentFloor() < ctrl.targetFloor()) {
        ctrl.stepUp();
    } else if (ctrl.currentFloor() > ctrl.targetFloor()) {
        ctrl.stepDown();
    }

    std::cout << "[Менеджер] Текущий этаж: " << ctrl.currentFloor() << std::endl;
    notifyStateChanged();

    if (ctrl.hasPendingFloor(ctrl.currentFloor())) {
        arriveAtFloor();
        return;
    }

    if (ctrl.currentFloor() == ctrl.targetFloor()) {
        pickNextTarget();
        if (ctrl.targetFloor() != ctrl.currentFloor()) {
            std::cout << "[Менеджер] Промежуточная смена цели: этаж " << ctrl.targetFloor() << std::endl;
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
            std::cout << "[Менеджер] Смена цели без остановки: этаж " << ctrl.targetFloor() << std::endl;
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

    std::cout << "[Менеджер] Прибытие на этаж " << ctrl.currentFloor() << std::endl;
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

void ElevatorManager::onDoorOpenTimerElapsed() {
    _elevator->door().completeOpen();
    if (_timers.startWaitTimer) {
        _timers.startWaitTimer(ElevatorConfig::FLOOR_WAIT_MS);
    }
}

void ElevatorManager::onWaitTimerElapsed() {
    _elevator->door().close();
    if (_timers.startDoorCloseTimer) {
        _timers.startDoorCloseTimer(ElevatorConfig::DOOR_CLOSE_MS);
    }
}

void ElevatorManager::onDoorCloseTimerElapsed() {
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
        std::cout << "[Менеджер] Очередь заявок пуста" << std::endl;
        notifyStateChanged();
        return;
    }

    pickNextTarget();
    std::cout << "[Менеджер] Следующая цель: этаж " << ctrl.targetFloor() << " ("
              << ctrl.directionName() << ")" << std::endl;
    notifyStateChanged();

    schedule();
}
