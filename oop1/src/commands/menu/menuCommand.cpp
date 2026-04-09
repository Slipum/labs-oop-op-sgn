#include "menuCommand.h"

SumAreasCommand::SumAreasCommand(MenuCommand* owner, vector<Figure*>* figures)
    : ICommand(figures), owner(owner) {}
void SumAreasCommand::exec() {
    IsEmptyFigures();
    double sum = 0.0;
    for (size_t i = 0; i < figures->size(); ++i) sum += figures->at(i)->getArea();
    cout << "Сумма площадей всех фигур: " << sum << endl;
}
string SumAreasCommand::intro() { return "Сумма площадей всех фигур"; }




SortByAreaCommand::SortByAreaCommand(MenuCommand* owner, vector<Figure*>* figures)
    : ICommand(figures), owner(owner) {}
bool SortByAreaCommand::compare(Figure* a, Figure* b) { return a->getArea() < b->getArea(); }
void SortByAreaCommand::exec() {
    IsEmptyFigures();
    std::sort(figures->begin(), figures->end(), compare);
    cout << "Фигуры отсортированы по площади (по возрастанию)" << endl;
}
string SortByAreaCommand::intro() { return "Сортировать по площади (по возрастанию)"; }




ExitCommand::ExitCommand(vector<Figure*>* figures) : ICommand(figures) {}
void ExitCommand::exec() { throw std::runtime_error("EXIT"); }
string ExitCommand::intro() { return "Выход"; }