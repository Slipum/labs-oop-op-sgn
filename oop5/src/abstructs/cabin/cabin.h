#ifndef OOP5_LOGIC_CABIN_H
#define OOP5_LOGIC_CABIN_H

#include <string>

#include "entrypoint/entrypoint.h"

class ICabin {
public:
    virtual ~ICabin() = default;

    virtual CabinState state() const = 0;
    // virtual const std::string &stateName() const = 0;

    virtual void prepareToMove() = 0;
    virtual void startMoving() = 0;
    virtual void stop() = 0;
    virtual void block() = 0;
    virtual void unblock() = 0;
};

class ElevatorCabin : public ICabin {
public:
    // ElevatorCabin() : _stateName(cabinStateToString(_state)) {}
    ElevatorCabin() = default;

    CabinState state() const override { return _state; }
    // const std::string &stateName() const override { return _stateName; }

    void prepareToMove() override { setState(CabinState::PreparingToMove); }
    void startMoving() override { setState(CabinState::Moving); }
    void stop() override { setState(CabinState::Stopped); }
    void block() override { setState(CabinState::Blocked); }
    void unblock() override { setState(CabinState::Unblocked); }

private:
    void setState(CabinState state);
    const std::string cabinStateToString(CabinState state);

    CabinState _state = CabinState::Stopped;
    // std::string _stateName;
};

#endif // OOP5_LOGIC_CABIN_H
