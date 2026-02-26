#include "stdfree.h"
#include <iostream>

void freeInput() {
    std::cin.clear();
    std::cin.ignore(32767,'\n');
}
