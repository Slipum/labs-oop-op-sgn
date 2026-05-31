#ifndef OOP5_BUILDER_H
#define OOP5_BUILDER_H
#include "abstructs/elevator/elevator.h"

class IBuilder {
public:
    virtual IElevator* createElevator(int countFloor) = 0;
};

class ElevatorBuilder : public IBuilder {
public:
    IElevator* createElevator(int countFloor) override;
};

#endif //OOP5_BUILDER_H
