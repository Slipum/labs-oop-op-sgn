#ifndef OOP5_DOOR_H
#define OOP5_DOOR_H
#include <iostream>

class IDoor {};

class Door : public IDoor {
public:
    Door() {
        std::cout << "Default door" << std::endl;
    }
};

#endif //OOP5_DOOR_H
