#include "door.h"

#include <iostream>
//
// const char *doorStateToString(DoorState state) {
//     switch (state) {
//     case DoorState::Opening:
//         return "открываются";
//     case DoorState::Open:
//         return "открыты";
//     case DoorState::Closing:
//         return "закрываются";
//     case DoorState::Closed:
//         return "закрыты";
//     }
//     return "неизвестно";
// }

void ElevatorDoor::open() {
    if (_state == DoorState::Open || _state == DoorState::Opening) return;
    setState(DoorState::Opening);
    // std::cout << "[Двери] Начало открытия" << std::endl;
}

void ElevatorDoor::close() {
    if (_state == DoorState::Closed || _state == DoorState::Closing) return;
    setState(DoorState::Closing);
    // std::cout << "[Двери] Начало закрытия" << std::endl;
}

void ElevatorDoor::completeOpen() {
    if (_state != DoorState::Opening) return;
    setState(DoorState::Open);
    // std::cout << "[Двери] Открыты" << std::endl;
}

void ElevatorDoor::completeClose() {
    if (_state != DoorState::Closing) return;
    setState(DoorState::Closed);
    // std::cout << "[Двери] Закрыты" << std::endl;
}

void ElevatorDoor::setState(DoorState state) {
    if (_state == state) return;
    _state = state;
    // _stateName = doorStateToString(state);
    // std::cout << "[Двери] Состояние: " << _stateName << std::endl;
}
