#ifndef OOP5_LOGIC_BUILDER_H
#define OOP5_LOGIC_BUILDER_H

#include <memory>

#include "abstructs/cabin/cabin.h"
#include "abstructs/controller/controller.h"
#include "abstructs/door/door.h"
#include "abstructs/elevator/elevator.h"

class ElevatorBuilder {
public:
    ElevatorBuilder() = default;
    std::unique_ptr<Elevator> build(int startFloor = 1);

private:
    std::unique_ptr<ICabin> _cabin;
    std::unique_ptr<IController> _controller;
    std::unique_ptr<IDoor> _door;
};

#endif // OOP5_LOGIC_BUILDER_H
