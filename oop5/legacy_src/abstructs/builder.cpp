#include "builder.h"

IElevator* ElevatorBuilder::createElevator() {
    IElevator* elevator = new Elevator;
    elevator->setCabin(std::make_unique<Cabin>());
    elevator->setDoor(std::make_unique<Door>());
    return elevator;
}
