#ifndef MENU_H
#define MENU_H

#include "logic.h"

enum MenuChoices {
    ADD = 1,
    ALL_PARAMS,
    ALL_AREA,
    SUM_AREAS,
    SORT,
    DEL_NUM,
    DEL_AREA,
    EXIT,
};

class Menu {
private:
    vector<Figure*> figures;

    int validOption(int *option);
    void printMenu();
    bool correctFigure(int figure);

public:
    int run(vector<Figure*>* figures);
};

#endif //MENU_H
