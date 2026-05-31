#ifndef OOP5_FACADE_H
#define OOP5_FACADE_H
#include <queue>
#include <thread>

#include "abstructs/builder/builder.h"

class IFacade {
public:

    virtual void AcceptFromFloor(int floor) = 0; // - принимать вызовы с этажей;
    virtual void AcceptFromCabin(int floor) = 0; // - принимать команды из кабины;
    virtual void ToFloor(int floor) = 0; // - перемещаться между этажами;

    // virtual void SetState() = 0; // - открывать и закрывать двери; TODO: вшито в ToFloor

    // virtual bool IsUpMove() = 0; // - определять направление движения; TODO: пока нет смысла

    // 1. обрабатывать несколько заявок; TODO: нужно хранить очередь

    // -----------------------------------------------------------
    // 2. останавливаться на промежуточных
    // этажах при наличии вызова по пути следования.
    // TODO: делать проверку на каждом этаже нужно ли остановиться
    // -----------------------------------------------------------
};

class ElevatorFacade : public IFacade {
private:
    void ToFloor(int floor) override;
    void ProcessRequests();

public:
    ElevatorFacade(int floor);
    ~ElevatorFacade();

    void AcceptFromCabin(int floor) override;
    void AcceptFromFloor(int floor) override;
private:
    IElevator* _elevator;
    std::vector<int> _floors;

    std::thread _thread;
};

#endif //OOP5_FACADE_H
