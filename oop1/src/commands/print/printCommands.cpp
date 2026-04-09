#include "printCommands.h"

PrintAllCommand::PrintAllCommand(MenuCommand* owner, vector<Figure*>* figures)
    : ICommand(figures), owner(owner) {}

void PrintAllCommand::PrintBy() {
    IsEmptyFigures();
    for (size_t i = 0; i < figures->size(); ++i) {
        cout << "[" << i + 1 << "] ";
        by(i);
    }
}



void PrintAllCommand::exec() { return; }
void PrintAllCommand::by(int index) { return; }



PrintAllParamsCommand::PrintAllParamsCommand(MenuCommand* owner, vector<Figure*>* figures)
    : PrintAllCommand(owner, figures) {}
void PrintAllParamsCommand::by(int index) { figures->at(index)->printParam(); }
void PrintAllParamsCommand::exec() { PrintBy(); }
string PrintAllParamsCommand::intro() { return "Вывести все фигуры с параметрами"; }



PrintAllAreasCommand::PrintAllAreasCommand(MenuCommand* owner, vector<Figure*>* figures)
    : PrintAllCommand(owner, figures) {}
void PrintAllAreasCommand::by(int index) { figures->at(index)->printArea(); }
void PrintAllAreasCommand::exec() { PrintBy(); }
string PrintAllAreasCommand::intro() { return "Вывести все фигуры с площадями"; }
