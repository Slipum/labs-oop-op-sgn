#ifndef OOP5_CONTROLLER_H
#define OOP5_CONTROLLER_H

class IController {
public:
    virtual ~IController() = default;

    virtual bool isMoving() = 0;
    virtual void updateMove(bool move) = 0;
    virtual void setFloor(int floor) = 0;
    virtual int getFloor() = 0;
};

class ElevatorController : public IController {
public:
    ElevatorController(int floor, int countFloor) : _floor(floor), _countFloor(countFloor) {};

    bool isMoving() override { return _isMoving; };
    void updateMove(bool move) override { _isMoving = move; };

    void setFloor(int floor) override;
    int getFloor() override { return _floor; };
private:
    int _countFloor;
    int _floor;
    bool _isMoving = false;
};

#endif //OOP5_CONTROLLER_H
