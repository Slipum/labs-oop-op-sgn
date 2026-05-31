#ifndef OOP5_BUILDER_H
#define OOP5_BUILDER_H
#include "elevator/elevator.h"

class IBuilder {
public:
    ~IBuilder() = default;
    virtual IElevator* createElevator() = 0;
};

class ElevatorBuilder : public IBuilder {
public:
    IElevator* createElevator() override;
};

#endif //OOP5_BUILDER_H
