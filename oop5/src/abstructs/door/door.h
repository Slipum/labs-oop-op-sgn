#ifndef OOP5_LOGIC_DOOR_H
#define OOP5_LOGIC_DOOR_H

#include <string>

#include "entrypoint/entrypoint.h"

class IDoor {
public:
    virtual ~IDoor() = default;

    virtual DoorState state() const = 0;
    // virtual const std::string &stateName() const = 0;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual void completeOpen() = 0;
    virtual void completeClose() = 0;
};

class ElevatorDoor : public IDoor {
public:
    DoorState state() const override { return _state; }
    // const std::string &stateName() const override { return _stateName; }

    void open() override;
    void close() override;
    void completeOpen() override;
    void completeClose() override;

private:
    void setState(DoorState state);

    DoorState _state = DoorState::Closed;
    // std::string _stateName = "закрыты";
};

#endif // OOP5_LOGIC_DOOR_H
