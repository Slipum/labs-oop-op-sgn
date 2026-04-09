#ifndef MENU_H
#define MENU_H

#include <map>

#include "../command.h"
#include "../../bussines/logic.h"

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

class MenuCommand : public UtilsCommand {
    vector<Figure*>* figures;
    map<int, unique_ptr<ICommand>> choices;
    int option;

    void printMenu();
    void validOption();
public:
    virtual vector<Figure*>* getFigures() { return figures; };

    MenuCommand(vector<Figure*>* f);

    virtual void exec();
};

#endif //MENU_H
