#include "builder.h"

IElevator* ElevatorBuilder::createElevator(int countFloor) {
    Elevator* elevator = new Elevator(countFloor);
    elevator->setCabin(new ElevatorCabin());
    elevator->setController(new ElevatorController(elevator->getCountFloor(), countFloor));
    elevator->setDoor(new ElevatorDoor());
    return elevator;
}
