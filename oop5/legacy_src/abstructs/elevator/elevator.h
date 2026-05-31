#ifndef OOP5_ELEVATOR_H
#define OOP5_ELEVATOR_H

#include <iostream>
#include <memory>

#include "abstructs/cabin/cabin.h"
#include "abstructs/door/door.h"


class IElevator {
public:
    ~IElevator() = default;

    virtual void setFloor(int floor) = 0;
    virtual void setCabin(std::unique_ptr<ICabin> cabin) = 0;
    virtual void setDoor(std::unique_ptr<IDoor> door) = 0;

    virtual int getFloor() = 0;
    virtual std::unique_ptr<ICabin> getCabin() = 0;
    virtual std::unique_ptr<IDoor> getDoor() = 0;

    virtual void acceptFromFloor(int floor) = 0; // - принимать вызовы с этажей;
    virtual void acceptFromCabin(int floor) = 0; // - принимать команды из кабины;
    virtual void toFloor(int floor) = 0; // - перемещаться между этажами;

    virtual void setState() = 0; // - открывать и закрывать двери;

    virtual bool isUpMove() = 0; // - определять направление движения;
};

class Elevator : public IElevator {
public:
    Elevator(int floor = 2) : _CountFloor(floor) {};

    void setFloor(int floor) override { _CountFloor = floor; }
    int getFloor() override { return _CountFloor; }

    void setCabin(std::unique_ptr<ICabin> cabin) override { _cabin = std::move(cabin); }
    std::unique_ptr<ICabin> getCabin() override { return std::move(_cabin); }

    void acceptFromCabin(int floor) override {};
    void acceptFromFloor(int floor) override {};
    void toFloor(int floor) override {};
    void setState() override {};
    bool isUpMove() override {};

private:
    int _CountFloor;
    int _currentFloor = 0;
    std::unique_ptr<ICabin> _cabin;

    std::priority_queue<int> _floorQueue;
};

#endif //OOP5_ELEVATOR_H
