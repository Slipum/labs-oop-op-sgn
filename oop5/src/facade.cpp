#include "facade.h"

#include <exception>
#include <iostream>

ElevatorFacade::ElevatorFacade(int floor) {
    ElevatorBuilder builder;
    _elevator = builder.createElevator(floor);

    _thread = std::thread(&ElevatorFacade::ProcessRequests, this);
}

void ElevatorFacade::AcceptFromFloor(int floor) {  }

void ElevatorFacade::ToFloor(int floor) {
    try {
        _elevator->setFloor(floor);
        _elevator->getDoor()->open();
        _elevator->getDoor()->close();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void ElevatorFacade::AcceptFromCabin(int floor) {
    _floors.push_back(floor);
}

void ElevatorFacade::ProcessRequests() {
    while (!_floors.empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        ToFloor(_floors.back());
        _floors.pop_back();
    }
}

ElevatorFacade::~ElevatorFacade() {
    if (_thread.joinable()) {
        _thread.join();
    }
}
