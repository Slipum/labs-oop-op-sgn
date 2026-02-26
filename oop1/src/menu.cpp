#include "menu.h"
#include <cstdio>

int validOption(int *option) {
    if (scanf("%d", option) != 1) {
        cout << "Пожалуйста введите цифру." << endl;
        freeInput();
        return 1;
    }
    return 0;
}

void printMenu() {
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

bool correctFigure(int figure) {
    int i = 0;
    switch (figure) {
        case CIRCLE: i++;
        case RECTANGLE: i++;
        case TRIANGLE: i++;
        case POLYGON: i++;
    }

    return i != 0;
}

int menu(vector<Figure*>* figures) {
    int option;
    printMenu();
    if (validOption(&option)) return 1;
    freeInput();
    switch (option) {
        case ADD:
            while (!correctFigure(addFigure(figures))) {}
            break;
        case ALL_PARAMS:
            printAllParams(*figures);
            break;
        case ALL_AREA:
            printAllAreas(*figures);
            break;
        case SUM_AREAS:
            sumAreas(*figures);
            break;
        case SORT:
            sortByArea(figures);
            break;
        case DEL_NUM:
            deletePerNum(figures);
            break;
        case DEL_AREA:
            deletePerArea(figures);
            break;
        case EXIT:
            break;
        default:
            cout << "Некорректный пункт. Попробуйте другой из предложенных: " << endl;
            break;
    }
    return option;
}