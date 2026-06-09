#include "elevator.h"

Elevator::Elevator(std::unique_ptr<ICabin> cabin, std::unique_ptr<IController> controller, std::unique_ptr<IDoor> door)
    : _cabin(std::move(cabin)),
    _controller(std::move(controller)),
    _door(std::move(door)) {}

