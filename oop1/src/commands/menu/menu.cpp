#include "menu.h"

#include <iomanip>

#include "../add figures/addFigure.h"

#include "menuCommand.h"
#include "../command.h"
#include "../print/printCommands.h"
#include "../delete/deleteCommands.h"

MenuCommand::MenuCommand(vector<Figure*>* f) : figures(f) {
    choices[ADD] = make_unique<AddFigureCommand>(this, figures);
    choices[ALL_PARAMS] = make_unique<PrintAllParamsCommand>(this, figures);
    choices[ALL_AREA] = make_unique<PrintAllAreasCommand>(this, figures);
    choices[SUM_AREAS] = make_unique<SumAreasCommand>(this, figures);
    choices[SORT] = make_unique<SortByAreaCommand>(this, figures);
    choices[DEL_NUM] = make_unique<DeletePerNumCommand>(this, figures);
    choices[DEL_AREA] = make_unique<DeletePerAreaCommand>(this, figures);
    choices[EXIT] = make_unique<ExitCommand>(figures);
}


void MenuCommand::validOption() {
    if (cin.peek() == EOF || cin.eof()) {
        cout << endl;
        option = EXIT;
        return;

    }
    cin >> option;
    if (cin.fail() || !validEnd()) {
        freeInput();
        throw runtime_error("Пожалуйста введите цифру.");
    }
}

void MenuCommand::printMenu() {
    cout << "+=================== МЕНЮ ===================+" << endl;
    for (auto &p : choices) {
        cout << "  " << p.first << ". " << p.second->intro() << endl;
    }
    cout << "+============================================+" << endl;
    cout << ">> ";
}

void MenuCommand::exec() {
    printMenu();
    validOption();
    freeInput();

    auto it = choices.find(option);
    if (it == choices.end()) {
        throw runtime_error("Некорректный пункт.");
    }
    it->second->exec();
}