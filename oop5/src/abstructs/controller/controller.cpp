#include "controller.h"

#include <iostream>

#include "entrypoint/entrypoint.h"

namespace {
const char *controllerStateToString(ControllerState state) {
    switch (state) {
    case ControllerState::Free:
        return "свободен";
    case ControllerState::Moving:
        return "движение";
    case ControllerState::UpdatingTarget:
        return "обновление цели";
    case ControllerState::ReachingTarget:
        return "достижение целевого этажа";
    }
    return "неизвестно";
}

const char *directionToString(MoveDirection direction) {
    switch (direction) {
    case MoveDirection::Idle:
        return "простой";
    case MoveDirection::Up:
        return "вверх";
    case MoveDirection::Down:
        return "вниз";
    }
    return "неизвестно";
}
} // namespace

ElevatorController::ElevatorController(int startFloor)
    : _currentFloor(startFloor), _targetFloor(startFloor) {
    std::cout << "[Контроллер] Инициализация на этаже " << _currentFloor << std::endl;
}

bool ElevatorController::hasPendingFloor(int floor) const {
    return _pendingFloors.contains(floor);
}

void ElevatorController::addPendingFloor(int floor) {
    _pendingFloors.insert(floor);
}

void ElevatorController::removePendingFloor(int floor) {
    _pendingFloors.erase(floor);
}

void ElevatorController::setState(ControllerState state) {
    if (_controllerState == state) {
        return;
    }
    _controllerState = state;
    _controllerStateName = controllerStateToString(state);
    std::cout << "[Контроллер] Состояние: " << _controllerStateName << std::endl;
}

void ElevatorController::setDirection(MoveDirection direction) {
    if (_direction == direction) {
        return;
    }
    _direction = direction;
    _directionName = directionToString(direction);
    std::cout << "[Контроллер] Направление: " << _directionName << std::endl;
}

void ElevatorController::stepUp() {
    ++_currentFloor;
    setDirection(MoveDirection::Up);
}

void ElevatorController::stepDown() {
    --_currentFloor;
    setDirection(MoveDirection::Down);
}

bool ElevatorController::isValidFloor(int floor) const {
    return floor >= ElevatorConfig::MIN_FLOOR && floor <= ElevatorConfig::FLOOR_COUNT;
}
