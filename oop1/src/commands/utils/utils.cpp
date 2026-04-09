#include "utils.h"

#include <iostream>

void UtilsCommand::freeInput() {
    std::cin.clear();
    std::cin.ignore(LONG_MAX,'\n');
}

bool UtilsCommand::validEnd() {
    if (std::cin.peek() != '\n') {
        return false;
    }
    return true;
}