#include "door.h"
#include <iostream>

void ElevatorDoor::close() {
    _isOpen = false;
    std::cout << "Elevator door closed" << std::endl;
}

void ElevatorDoor::open() {
    _isOpen = true;
    std::cout << "Elevator door opened" << std::endl;
}
