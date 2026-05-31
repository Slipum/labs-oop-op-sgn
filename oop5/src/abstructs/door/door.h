#ifndef OOP5_DOOR_H
#define OOP5_DOOR_H

class IDoor {
public:
    virtual ~IDoor() = default;

    virtual bool isOpen() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
};

class ElevatorDoor : public IDoor {
public:
    ElevatorDoor() {}
    ~ElevatorDoor() {}

    bool isOpen() override { return _isOpen; }
    void open() override { _isOpen = true; }
    void close() override { _isOpen = false; }
private:
    bool _isOpen = false;
};

#endif //OOP5_DOOR_H
