#include "deleteCommands.h"

DeleteCommand::DeleteCommand(MenuCommand* owner, vector<Figure*>* figures)
    : ICommand(figures), owner(owner) {}

void DeleteCommand::deleteClass() {
    if (!figures || index < 0 || index >= static_cast<int>(figures->size()))
        throw std::out_of_range("Неправильный индекс для удаления.");
    delete figures->at(static_cast<size_t>(index));
    figures->erase(figures->begin() + index);
}



DeletePerNumCommand::DeletePerNumCommand(MenuCommand* owner, vector<Figure*>* figures)
    : DeleteCommand(owner, figures) {}

void DeletePerNumCommand::exec() {
    IsEmptyFigures();
    InputNum();
    deleteClass();
}

void DeletePerNumCommand::InputNum() {
    cout << "Введите номер фигуры для удаления: ";
    if (!(std::cin >> index)) {
        std::cin.clear();
        std::string tmp;
        std::getline(std::cin, tmp);
        throw std::runtime_error("Некорректный ввод номера.");
    }
    index--;
    if (index < 0 || index >= static_cast<int>(figures->size()))
        throw std::range_error("Такой фигуры нет. Попробуйте ввести корректный номер фигуры.");
}

string DeletePerNumCommand::intro() { return "Удалить фигуру по номеру"; }



DeletePerAreaCommand::DeletePerAreaCommand(MenuCommand* owner, vector<Figure*>* figures)
    : DeleteCommand(owner, figures), area(0) {}

void DeletePerAreaCommand::exec() {
    IsEmptyFigures();
    InputArea();
    IsEmptyIndexes();
    for (int i = static_cast<int>(indexes.size()) - 1; i >= 0; --i) {
        index = indexes[i];
        deleteClass();
    }
}

void DeletePerAreaCommand::IsEmptyIndexes() {
    getIndexes();
    if (indexes.empty())
        throw std::range_error("Таких объектов нет. Попробуйте ввести другую площадь.");
}

void DeletePerAreaCommand::InputArea() {
    cout << "Фигуры больше этой площади удаляться. Введите площадь: ";
    if (!(std::cin >> area)) {
        std::cin.clear();
        std::string tmp;
        std::getline(std::cin, tmp);
        throw std::runtime_error("Некорректный ввод площади.");
    }
    if (area <= 0)
        throw std::range_error("Площадь не может быть отрицательной или нулевой. Попробуйте ввести корректную площадь.");
}

void DeletePerAreaCommand::getIndexes() {
    for (size_t i = 0; i < figures->size(); ++i)
        if (figures->at(i)->getArea() > area) indexes.push_back(static_cast<int>(i));
}

string DeletePerAreaCommand::intro() { return "Удалить фигуры > площади"; }
