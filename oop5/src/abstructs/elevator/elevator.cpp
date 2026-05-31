#include "elevator.h"

#include <iostream>
#include <ostream>

Elevator::~Elevator() {
    delete _cabin;
    delete _door;
    delete _controller;
}

void Elevator::setFloor(int floor) {
    _controller->setFloor(floor);
    _currentFloor = floor;
    std::cout << "Elevator arrived on the floor: " << floor << std::endl;
}
