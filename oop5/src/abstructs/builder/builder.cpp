#include "builder.h"

#include <stdexcept>

#include "abstructs/cabin/cabin.h"
#include "abstructs/controller/controller.h"
#include "abstructs/door/door.h"
#include "manager/manager.h"

ElevatorBuilder::ElevatorBuilder() = default;

ElevatorBuilder &ElevatorBuilder::withCabin(std::unique_ptr<ICabin> cabin) {
    _cabin = std::move(cabin);
    return *this;
}

ElevatorBuilder &ElevatorBuilder::withController(std::unique_ptr<IController> controller) {
    _controller = std::move(controller);
    return *this;
}

ElevatorBuilder &ElevatorBuilder::withDoor(std::unique_ptr<IDoor> door) {
    _door = std::move(door);
    return *this;
}

ElevatorBuilder &ElevatorBuilder::withDefaults(int startFloor) {
    _cabin = std::make_unique<ElevatorCabin>();
    _controller = std::make_unique<ElevatorController>(startFloor);
    _door = std::make_unique<ElevatorDoor>();
    return *this;
}

std::unique_ptr<Elevator> ElevatorBuilder::build() {
    if (!_cabin || !_controller || !_door) {
        throw std::runtime_error("ElevatorBuilder: не заданы cabin, controller или door");
    }
    return std::make_unique<Elevator>(std::move(_cabin), std::move(_controller), std::move(_door));
}

std::unique_ptr<ElevatorManager> ElevatorBuilder::buildManager() {
    return std::make_unique<ElevatorManager>(build());
}
