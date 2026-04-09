#include "command.h"

#include <stdexcept>

void ICommand::IsEmptyFigures() {
    if (!figures || figures->empty())
        throw std::runtime_error("Массив фигур пуст. Попробуйте сначала добавить фигуру.");
}

void ICommand::setNameFigure(Figure* f) {
    string name;
    do {
        cout << "Введите имя: ";
        getline(cin, name, '\n');
    } while (!f->setName(name));
}