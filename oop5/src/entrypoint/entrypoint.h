#ifndef OOP5_LOGIC_ELEVATOR_TIMER_HOST_H
#define OOP5_LOGIC_ELEVATOR_TIMER_HOST_H

#include <functional>

enum class DoorState { Opening, Open, Closing, Closed };

enum class CabinState { Stopped, PreparingToMove, Moving, Blocked, Unblocked };

enum class ControllerState { Free, Moving, UpdatingTarget, ReachingTarget };

enum class MoveDirection { Idle, Up, Down };


struct ElevatorTimerHost {
    std::function<void(int ms)> startMoveTimer;
    std::function<void()> stopMoveTimer;
    std::function<void(int ms)> startWaitTimer;
    std::function<void(int ms)> startDoorOpenTimer;
    std::function<void(int ms)> startDoorCloseTimer;
};

enum ElevatorConfig {
    FLOOR_COUNT = 5,
    MIN_FLOOR = 1,

    WAIT_MS = 1000,
    DOOR_OPEN_MS = 700,
    DOOR_CLOSE_MS = 700,
    FLOOR_WAIT_MS = 2000,
};

#endif // OOP5_LOGIC_ELEVATOR_TIMER_HOST_H
