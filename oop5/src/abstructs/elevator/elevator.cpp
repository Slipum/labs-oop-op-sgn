#include "elevator.h"

Elevator::~Elevator() {
    delete _cabin;
    delete _door;
    delete _controller;
}

void Elevator::setFloor(int floor) {
    _controller->setFloor(floor);
    _currentFloor = floor;
}
