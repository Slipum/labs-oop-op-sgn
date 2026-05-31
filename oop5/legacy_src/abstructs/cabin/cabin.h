#ifndef OOP5_CABIN_H
#define OOP5_CABIN_H
#include <iostream>
#include <ostream>

class ICabin {
public:
};

class Cabin : public ICabin {
public:
    Cabin() {
        std::cout << "Default cabin" << std::endl;
    }
};

#endif //OOP5_CABIN_H
