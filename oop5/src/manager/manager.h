#ifndef OOP5_MANAGER_H
#define OOP5_MANAGER_H

class IManager {
public:
    virtual ~IManager() = default;
};

class ElevatorManager : public IManager {
public:
    ElevatorManager() {}
};

#endif //OOP5_MANAGER_H
