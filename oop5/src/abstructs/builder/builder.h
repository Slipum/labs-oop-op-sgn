#ifndef OOP5_LOGIC_BUILDER_H
#define OOP5_LOGIC_BUILDER_H

#include <memory>

#include "abstructs/cabin/cabin.h"
#include "abstructs/controller/controller.h"
#include "abstructs/door/door.h"
#include "abstructs/elevator/elevator.h"
#include "manager/manager.h"

class ElevatorBuilder {
public:
    ElevatorBuilder();

    ElevatorBuilder &withCabin(std::unique_ptr<ICabin> cabin);
    ElevatorBuilder &withController(std::unique_ptr<IController> controller);
    ElevatorBuilder &withDoor(std::unique_ptr<IDoor> door);
    ElevatorBuilder &withDefaults(int startFloor = 1);

    std::unique_ptr<Elevator> build();
    std::unique_ptr<ElevatorManager> buildManager();

private:
    std::unique_ptr<ICabin> _cabin;
    std::unique_ptr<IController> _controller;
    std::unique_ptr<IDoor> _door;
};

#endif // OOP5_LOGIC_BUILDER_H
