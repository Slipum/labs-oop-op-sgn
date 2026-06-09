#include "cabin.h"
#include <iostream>

// const std::string ElevatorCabin::cabinStateToString(CabinState state) {
//     switch (state) {
//         case CabinState::Stopped: return "остановка";
//         case CabinState::PreparingToMove: return "подготовка к движению";
//         case CabinState::Moving: return "движение";
//         case CabinState::Blocked: return "заблокирована";
//         case CabinState::Unblocked: return "разблокирована";
//     }
// }

void ElevatorCabin::setState(CabinState state) {
    if (_state == state) return;

    _state = state;
    // _stateName = cabinStateToString(state);
    // std::cout << "[Кабина] Состояние: " << _stateName << std::endl;
}
