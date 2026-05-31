#ifndef OOP5_LOGIC_MANAGER_H
#define OOP5_LOGIC_MANAGER_H

#include <functional>
#include <memory>

#include "entrypoint/entrypoint.h"
#include "abstructs/elevator/elevator.h"

class ElevatorManager {
public:
    using StateChangedCallback = std::function<void()>;

    explicit ElevatorManager(std::unique_ptr<Elevator> elevator);

    void setTimerHost(ElevatorTimerHost host);
    void setStateChangedCallback(StateChangedCallback callback);

    Elevator &elevator();
    const Elevator &elevator() const;

    void callFromFloor(int floor);
    void callFromCabin(int floor);

    void onMoveTimerElapsed();
    void onWaitTimerElapsed();
    void onDoorOpenTimerElapsed();
    void onDoorCloseTimerElapsed();

private:
    void enqueueFloor(int floor, const char *source);
    void schedule();
    void pickNextTarget();
    void startMoving();
    void continueMoving();
    void arriveAtFloor();
    void beginDoorCycle();
    void finishStopAtFloor();
    void notifyStateChanged();

    std::unique_ptr<Elevator> _elevator;
    ElevatorTimerHost _timers;
    StateChangedCallback _onStateChanged;
};

#endif // OOP5_LOGIC_MANAGER_H
