#ifndef MENU_COMMAND_H
#define MENU_COMMAND_H

#include "../../bussines/logic.h"
#include "menu.h"

class SumAreasCommand : public ICommand {
    MenuCommand* owner;
public:
    SumAreasCommand(MenuCommand* owner, vector<Figure*>* figures);

    void exec() override;
    string intro() override;
};

class SortByAreaCommand : public ICommand {
    MenuCommand* owner;
    static bool compare(Figure* a, Figure* b);
public:
    SortByAreaCommand(MenuCommand* owner, vector<Figure*>* figures);

    void exec() override;
    string intro() override;
};

class ExitCommand: public ICommand {
public:
    ExitCommand(vector<Figure*>* figures);

    void exec() override;
    string intro() override;
};

#endif //MENU_COMMAND_H
