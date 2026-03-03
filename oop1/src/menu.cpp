#include "menu.h"
#include "validEnd.h"
#include "choices.h"
#include "stdfree.h"

int Menu::validOption(int* option) {
    if (cin.peek() == EOF || cin.eof()) {
        cout << endl;
        cout << "Некорректный ввод." << endl;
        *option = EXIT;
        freeInput();
        return 0;
    }
    cin >> *option;
    if (cin.fail() || !validEnd(cin.peek())) {
        cout << "Пожалуйста введите цифру." << endl;
        freeInput();
        return 1;
    }
    return 0;
}

void Menu::printMenu() {
    cout << "+=================== МЕНЮ ===================+" << endl;
    cout << "| 1. Добавить фигуру                         |" << endl; // ADD
    cout << "| 2. Вывести все фигуры с параметрами        |" << endl; // ALL_PARAMS
    cout << "| 3. Вывести все фигуры с площадями          |" << endl; // ALL_AREA
    cout << "| 4. Сумма площадей всех фигур               |" << endl; // SUM_AREAS
    cout << "| 5. Сортировать по площади (по возрастанию) |" << endl; // SORT
    cout << "| 6. Удалить фигуру по номеру                |" << endl; // DEL_NUM
    cout << "| 7. Удалить фигуры > площади                |" << endl; // DEL_AREA
    cout << "| 8. Выход                                   |" << endl; // EXIT
    cout << "+============================================+" << endl;
    cout << ">> ";
}

bool Menu::correctFigure(int figure) {
    int i = 0;
    switch (figure) {
    case CIRCLE: i++;
    case RECTANGLE: i++;
    case TRIANGLE: i++;
    case POLYGON: i++;
    }

    return i != 0;
}

int Menu::run(vector<Figure*>* figures) {
    int option;
    this->printMenu();
    if (this->validOption(&option)) {
        return 1;
    }
    freeInput();

    Choices choice;
    switch (option) {
    case ADD:
        while (!this->correctFigure(choice.addFigure(figures))) {}
        break;
    case ALL_PARAMS:
        choice.printAllParams(*figures);
        break;
    case ALL_AREA:
        choice.printAllAreas(*figures);
        break;
    case SUM_AREAS:
        choice.sumAreas(*figures);
        break;
    case SORT:
        choice.sortByArea(figures);
        break;
    case DEL_NUM:
        choice.deletePerNum(figures);
        break;
    case DEL_AREA:
        choice.deletePerArea(figures);
        break;
    case EXIT:
        break;
    default:
        cout << "Некорректный пункт. Попробуйте другой из предложенных: " << endl;
        break;
    }
    return option;
}