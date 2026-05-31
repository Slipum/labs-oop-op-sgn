#ifndef OOP5_ELEVATOR_H
#define OOP5_ELEVATOR_H
#include "abstructs/cabin/cabin.h"
#include "abstructs/controller/controller.h"
#include "abstructs/door/door.h"

class IElevator {
public:
    virtual int getCountFloor() = 0;

    virtual void setFloor(int floor) = 0;
    virtual int getFloor() = 0;

    // virtual void setDoor(IDoor* door) = 0;
    // virtual void setCabin(ICabin* cabin) = 0;
    // virtual void setController(IController* controller) = 0;

    virtual IDoor* getDoor() = 0;
    virtual ICabin* getCabin() = 0;
    virtual IController* getController() = 0;
};

class Elevator : public IElevator {
public:
    Elevator(int countFloor) : _countFloor(countFloor) {};
    ~Elevator();

    int getCountFloor() override { return _countFloor; }

    void setDoor(IDoor* door) { _door = door; }
    void setCabin(ICabin* cabin) { _cabin = cabin; }
    void setController(IController* controller) { _controller = controller; }

    IDoor* getDoor() override { return _door; }
    ICabin* getCabin() override { return _cabin; }
    IController* getController() override { return _controller; }

    void setFloor(int floor) override;
    int getFloor() override { return _currentFloor; }
private:
    int _countFloor;
    int _currentFloor = 1;

    IDoor* _door;
    IController* _controller;
    ICabin* _cabin;
};

#endif //OOP5_ELEVATOR_H
