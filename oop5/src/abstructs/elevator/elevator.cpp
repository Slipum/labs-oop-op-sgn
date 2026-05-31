#include "elevator.h"

Elevator::Elevator(std::unique_ptr<ICabin> cabin, std::unique_ptr<IController> controller,
                   std::unique_ptr<IDoor> door)
    : _cabin(std::move(cabin)), _controller(std::move(controller)), _door(std::move(door)) {}

ICabin &Elevator::cabin() {
    return *_cabin;
}

IController &Elevator::controller() {
    return *_controller;
}

IDoor &Elevator::door() {
    return *_door;
}

const ICabin &Elevator::cabin() const {
    return *_cabin;
}

const IController &Elevator::controller() const {
    return *_controller;
}

const IDoor &Elevator::door() const {
    return *_door;
}
