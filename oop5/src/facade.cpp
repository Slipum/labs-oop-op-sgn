#include "facade.h"

#include "abstructs/builder/builder.h"

ElevatorFacade::ElevatorFacade() : _manager(std::make_unique<ElevatorManager>(ElevatorBuilder().build())) {}

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

void ElevatorFacade::onMove() {
    _manager->onMove();
}

void ElevatorFacade::onWait() {
    _manager->onWait();
}

void ElevatorFacade::onDoorOpen() {
    _manager->onDoorOpen();
}

void ElevatorFacade::onDoorClose() {
    _manager->onDoorClose();
}

ElevatorManager &ElevatorFacade::manager() {
    return *_manager;
}

Elevator &ElevatorFacade::elevator() {
    return _manager->elevator();
}
