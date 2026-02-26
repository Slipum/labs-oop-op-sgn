#ifndef MENU_H
#define MENU_H
#include "logic.h"

void printMenu();
int menu(vector<Figure*>* figures);

enum Menu {
    ADD = 1,
    ALL_PARAMS,
    ALL_AREA,
    SUM_AREAS,
    SORT,
    DEL_NUM,
    DEL_AREA,
    EXIT,
};



#endif //MENU_H
