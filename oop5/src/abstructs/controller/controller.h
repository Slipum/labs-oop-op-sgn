#ifndef OOP5_LOGIC_CONTROLLER_H
#define OOP5_LOGIC_CONTROLLER_H

#include <unordered_set>

#include "entrypoint/entrypoint.h"

class IController {
public:
    virtual ~IController() = default;

    virtual int currentFloor() const = 0;
    virtual int targetFloor() const = 0;
    virtual void setTargetFloor(int floor) = 0;

    virtual ControllerState state() const = 0;
    virtual MoveDirection direction() const = 0;
    // virtual const std::string &stateName() const = 0;
    // virtual const std::string &directionName() const = 0;

    virtual const std::unordered_set<int> &pendingFloors() const = 0;
    virtual bool hasPendingFloor(int floor) const = 0;
    virtual void addPendingFloor(int floor) = 0;
    virtual void removePendingFloor(int floor) = 0;

    virtual void setState(ControllerState state) = 0;
    virtual void setDirection(MoveDirection direction) = 0;
    virtual void stepUp() = 0;
    virtual void stepDown() = 0;

    virtual bool isValidFloor(int floor) const = 0;
};

class ElevatorController : public IController {
public:
    explicit ElevatorController(int startFloor = 1);

    int currentFloor() const override { return _currentFloor; }
    int targetFloor() const override { return _targetFloor; }
    void setTargetFloor(int floor) override { _targetFloor = floor; }

    ControllerState state() const override { return _controllerState; }
    MoveDirection direction() const override { return _direction; }
    // const std::string &stateName() const override { return _controllerStateName; }
    // const std::string &directionName() const override { return _directionName; }

    const std::unordered_set<int> &pendingFloors() const override { return _pendingFloors; }
    bool hasPendingFloor(int floor) const override;
    void addPendingFloor(int floor) override;
    void removePendingFloor(int floor) override;

    void setState(ControllerState state) override;
    void setDirection(MoveDirection direction) override;
    void stepUp() override;
    void stepDown() override;

    bool isValidFloor(int floor) const override;

private:
    int _currentFloor;
    int _targetFloor;
    std::unordered_set<int> _pendingFloors;

    ControllerState _controllerState = ControllerState::Free;
    MoveDirection _direction = MoveDirection::Idle;

    // std::string _controllerStateName = "свободен";
    // std::string _directionName = "простой";
};

#endif // OOP5_LOGIC_CONTROLLER_H
