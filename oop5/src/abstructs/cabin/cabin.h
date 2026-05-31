#ifndef OOP5_LOGIC_CABIN_H
#define OOP5_LOGIC_CABIN_H

#include <string>

#include "entrypoint/entrypoint.h"

class ICabin {
public:
    virtual ~ICabin() = default;

    virtual CabinState state() const = 0;
    virtual const std::string &stateName() const = 0;

    virtual void prepareToMove() = 0;
    virtual void startMoving() = 0;
    virtual void stop() = 0;
    virtual void block() = 0;
    virtual void unblock() = 0;
};

class ElevatorCabin : public ICabin {
public:
    ElevatorCabin();

    CabinState state() const override { return _state; }
    const std::string &stateName() const override { return _stateName; }

    void prepareToMove() override;
    void startMoving() override;
    void stop() override;
    void block() override;
    void unblock() override;

private:
    void setState(CabinState state);

    CabinState _state = CabinState::Stopped;
    std::string _stateName;
};

#endif // OOP5_LOGIC_CABIN_H
