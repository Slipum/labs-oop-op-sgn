#include "cabin.h"

#include <iostream>

namespace {
const char *cabinStateToString(CabinState state) {
    switch (state) {
    case CabinState::Stopped:
        return "остановка";
    case CabinState::PreparingToMove:
        return "подготовка к движению";
    case CabinState::Moving:
        return "движение";
    case CabinState::Blocked:
        return "заблокирована";
    case CabinState::Unblocked:
        return "разблокирована";
    }
    return "неизвестно";
}
} // namespace

ElevatorCabin::ElevatorCabin() {
    _stateName = cabinStateToString(_state);
}

void ElevatorCabin::prepareToMove() {
    setState(CabinState::PreparingToMove);
}

void ElevatorCabin::startMoving() {
    setState(CabinState::Moving);
}

void ElevatorCabin::stop() {
    setState(CabinState::Stopped);
}

void ElevatorCabin::block() {
    setState(CabinState::Blocked);
}

void ElevatorCabin::unblock() {
    setState(CabinState::Unblocked);
}

void ElevatorCabin::setState(CabinState state) {
    if (_state == state) {
        return;
    }
    _state = state;
    _stateName = cabinStateToString(state);
    std::cout << "[Кабина] Состояние: " << _stateName << std::endl;
}
