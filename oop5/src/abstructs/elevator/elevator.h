#ifndef OOP5_LOGIC_ELEVATOR_H
#define OOP5_LOGIC_ELEVATOR_H

#include <memory>

#include "abstructs/cabin/cabin.h"
#include "abstructs/controller/controller.h"
#include "abstructs/door/door.h"

class Elevator {
public:
    Elevator(std::unique_ptr<ICabin> cabin, std::unique_ptr<IController> controller,
             std::unique_ptr<IDoor> door);

    ICabin &cabin();
    IController &controller();
    IDoor &door();

    const ICabin &cabin() const;
    const IController &controller() const;
    const IDoor &door() const;

private:
    std::unique_ptr<ICabin> _cabin;
    std::unique_ptr<IController> _controller;
    std::unique_ptr<IDoor> _door;
};

#endif // OOP5_LOGIC_ELEVATOR_H
