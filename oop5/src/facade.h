#ifndef OOP5_QT_FACADE_H
#define OOP5_QT_FACADE_H

#include <memory>

#include "entrypoint/entrypoint.h"
#include "abstructs/elevator/elevator.h"
#include "manager/manager.h"

class ElevatorFacade {
public:
    ElevatorFacade();
    explicit ElevatorFacade(std::unique_ptr<ElevatorManager> manager);

    void setTimerHost(ElevatorTimerHost host);
    void setStateChangedCallback(ElevatorManager::StateChangedCallback callback);

    void callFromFloor(int floor);
    void callFromCabin(int floor);

    void onMoveTimerElapsed();
    void onWaitTimerElapsed();
    void onDoorOpenTimerElapsed();
    void onDoorCloseTimerElapsed();

    ElevatorManager &manager();
    const ElevatorManager &manager() const;
    Elevator &elevator();
    const Elevator &elevator() const;

private:
    std::unique_ptr<ElevatorManager> _manager;
};

#endif // OOP5_QT_FACADE_H
