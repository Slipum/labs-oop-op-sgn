#include "controller.h"

#include <stdexcept>
#include <string>

void ElevatorController::setFloor(int floor) {
    if (floor < 1 || floor > _countFloor)
        throw std::out_of_range("Floor must be between 1 and " + std::to_string(_countFloor));
    this->_floor = floor;
}
