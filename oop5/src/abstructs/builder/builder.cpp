#include "builder.h"

#include "abstructs/cabin/cabin.h"
#include "abstructs/controller/controller.h"
#include "abstructs/door/door.h"
#include "manager/manager.h"

std::unique_ptr<Elevator> ElevatorBuilder::build(int startFloor) {
    _cabin = std::make_unique<ElevatorCabin>();
    _controller = std::make_unique<ElevatorController>(startFloor);
    _door = std::make_unique<ElevatorDoor>();
    return std::make_unique<Elevator>(std::move(_cabin), std::move(_controller), std::move(_door));
}