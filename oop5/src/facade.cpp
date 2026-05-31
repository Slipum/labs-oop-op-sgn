#include "facade.h"

#include "abstructs/builder/builder.h"

ElevatorFacade::ElevatorFacade() : _manager(ElevatorBuilder().withDefaults().buildManager()) {}

ElevatorFacade::ElevatorFacade(std::unique_ptr<ElevatorManager> manager) : _manager(std::move(manager)) {}

void ElevatorFacade::setTimerHost(ElevatorTimerHost host) {
    _manager->setTimerHost(std::move(host));
}

void ElevatorFacade::setStateChangedCallback(ElevatorManager::StateChangedCallback callback) {
    _manager->setStateChangedCallback(std::move(callback));
}

void ElevatorFacade::callFromFloor(int floor) {
    _manager->callFromFloor(floor);
}

void ElevatorFacade::callFromCabin(int floor) {
    _manager->callFromCabin(floor);
}

void ElevatorFacade::onMoveTimerElapsed() {
    _manager->onMoveTimerElapsed();
}

void ElevatorFacade::onWaitTimerElapsed() {
    _manager->onWaitTimerElapsed();
}

void ElevatorFacade::onDoorOpenTimerElapsed() {
    _manager->onDoorOpenTimerElapsed();
}

void ElevatorFacade::onDoorCloseTimerElapsed() {
    _manager->onDoorCloseTimerElapsed();
}

ElevatorManager &ElevatorFacade::manager() {
    return *_manager;
}

const ElevatorManager &ElevatorFacade::manager() const {
    return *_manager;
}

Elevator &ElevatorFacade::elevator() {
    return _manager->elevator();
}

const Elevator &ElevatorFacade::elevator() const {
    return _manager->elevator();
}
