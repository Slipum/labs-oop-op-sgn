#ifndef OOP5_FACADE_H
#define OOP5_FACADE_H

class ElevatorFacade {
public:

    virtual void AcceptFromFloor(int floor) = 0; // - принимать вызовы с этажей;
    virtual void AcceptFromCabin(int floor) = 0; // - принимать команды из кабины;
    virtual void ToFloor(int floor) = 0; // - перемещаться между этажами;

    virtual void SetState() = 0; // - открывать и закрывать двери;

    virtual bool IsUpMove() = 0; // - определять направление движения;

    // 1. обрабатывать несколько заявок; TODO: нужно хранить очередь

    // -----------------------------------------------------------
    // 2. останавливаться на промежуточных
    // этажах при наличии вызова по пути следования.
    // TODO: делать проверку на каждом этаже нужно ли остановиться
    // -----------------------------------------------------------
};

#endif //OOP5_FACADE_H
