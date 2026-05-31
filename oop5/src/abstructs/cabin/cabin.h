#ifndef OOP5_CABIN_H
#define OOP5_CABIN_H

enum State {
    WAIT,

    MOVING,
    STOPPING,
    STARTING,
    BLOCKED,
    UNBLOCKED
};

class ICabin {
public:
    virtual State getState() = 0;
    virtual void setState(State state) = 0;
};

class ElevatorCabin : public ICabin {
public:
    ElevatorCabin(State state = State::WAIT) : _state(state) {};

    State getState() override { return _state; }
    void setState(State state) override { _state = state; }
private:
    State _state;
};

#endif //OOP5_CABIN_H
