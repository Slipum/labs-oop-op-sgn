#include "menu.h"
#include <iostream>

void printFigureTypes() {
    cout << "1. Круг" << endl;
    cout << "2. Прямоугольник" << endl;
    cout << "3. Треугольник" << endl;
    cout << "4. Выпуклый многоугольник" << endl;
}

int addFigure(vector<Figure*>* figures) {
    int typeFigure;
    printFigureTypes();
    cout << "Введите тип фигуры: ";
    cin >> typeFigure;
    freeInput();
    switch (typeFigure) {
        case CIRCLE: {
            addCircle(figures);
            break;
        }
        case RECTANGLE: {
            addRectangle(figures);
            break;
        }
        case TRIANGLE: {
            addTriangle(figures);
            break;
        }
        case POLYGON: {
            addPolygon(figures);
            break;
        }
        default: {
            cout << "Некорректный пункт. Попробуйте другой из предложенных:" << endl;
            break;
        }
    }
    return typeFigure;
}

void setNameFigure(Figure* f) {
    string name;
    do {
        cout << "Введите имя: ";
        getline(cin, name, '\n');
    } while (!f->setName(name));
}

void addRectangle(vector<Figure*>* figures) {
    Rectangle* f = new Rectangle();
    setNameFigure(f);

    coord l;
    do {
        cout << "Введите координаты левого верхнего угла: ";
        cin >> l.x;
        cin >> l.y;
        if (cin.fail()) {
            cout << "Введите обе координаты левого верхнего угла." << endl;
            freeInput();
            continue;
        }
    } while (!f->setLeftCorner(l.x, l.y, cin.fail()));

    coord r;
    do {
        cout << "Введите координаты правого нижнего угла: ";
        cin >> r.x;
        cin >> r.y;
        if (cin.fail()) {
            cout << "Введите обе координаты правого нижнего угла." << endl;
            freeInput();
            continue;
        }
    } while (!f->setRightCorner(r.x, r.y, cin.fail()));
    figures->push_back(f);
}

void setTriangleCorner(Triangle* f, string corner) {
    coord c;
    bool success;
    do {
        cout << "Введите координаты " << corner << " угла: ";
        cin >> c.x;
        cin >> c.y;
        if (cin.fail()) {
            cout << "Введите обе координаты " << corner << " угла." << endl;
            freeInput();
            continue;
        }

        if (corner == "первого") {
            success = f->setA(c.x, c.y, cin.fail());
        } else if (corner == "второго") {
            success = f->setB(c.x, c.y, cin.fail());
        } else {
            success = f->setC(c.x, c.y, cin.fail());
        }
    } while (!success);
}

void setPolygonCorner(vector<coord>* corners, string corner) {
    coord c;

    cout << "Введите координаты " << corner << " угла: ";
    cin >> c.x;
    cin >> c.y;
    while (cin.fail()) {
        cout << "Введите обе координаты " << corner << " угла." << endl;
        freeInput();
        cout << "Введите координаты " << corner << " угла: ";
        cin >> c.x;
        cin >> c.y;
    };
    corners->push_back(c);
}

void addTriangle(vector<Figure*>* figures) {
    Triangle* f = new Triangle();
    setNameFigure(f);

    setTriangleCorner(f, "первого");
    setTriangleCorner(f, "второго");
    setTriangleCorner(f, "третьего");

    figures->push_back(f);
}

void addPolygon(vector<Figure*>* figures) {
    Polygon* f = new Polygon();
    setNameFigure(f);

    int corns;
    cout << "Введите количество вершин: ";
    cin >> corns;
    while (cin.fail() || corns <= 0) {
        cout << "Некоректное количество вершин." << endl;
        cout << "Введите количество вершин: ";
        freeInput();
        cin >> corns;
    }

    vector<coord> corners;
    for (int i = 1; i < corns+1; i++) {
        setPolygonCorner(&corners, (to_string(i) + "-ого"));
    }
    f->setCorners(corners);

    figures->push_back(f);
}

void addCircle(vector<Figure*>* figures) {
    Circle* f = new Circle();
    setNameFigure(f);

    coord c;
    do {
        cout << "Введите координаты центра: ";
        cin >> c.x;
        cin >> c.y;
        if (cin.fail()) {
            cout << "Введите обе координаты центра." << endl;
            freeInput();
            continue;
        }
    } while (!f->setCenter(c.x, c.y, cin.fail()));

    float r;
    do {
        cout << "Введите радиус: ";
        cin >> r;
    } while (!f->setRadius(r));
    figures->push_back(f);
}

void printAllParams(vector<Figure*> figures) {
    for (int i = 0; i < figures.size(); i++) {
        cout << "[" << i + 1 << "] ";
        figures[i]->printParam();
    }
}

void printAllAreas(vector<Figure*> figures) {
    for (int i = 0; i < figures.size(); i++) {
        cout << "[" << i + 1 << "] ";
        figures[i]->printArea();
    }
}

void sumAreas(vector<Figure*> figures) {
    double sum = 0;
    for (int i = 0; i < figures.size(); i++) {
        sum += figures[i]->getArea();
    }
    cout << "Сумма площадей всех фигур: " << sum << endl;
}

bool compare(Figure* a, Figure* b) {
    return a->getArea() < b->getArea();
};

void sortByArea(vector<Figure*>* figures) {
    sort(figures->begin(), figures->end(), compare);
    cout << "Фигуры отсортированы по площади (по возрастанию)" << endl;
}

void deleteClass(vector<Figure*>* arr, int index) {
    delete (*arr)[index];
    arr->erase(arr->begin() + index);
}

void deletePerNum(vector<Figure*>* figures) {
    if (figures->empty()) {
        cout << "Массив фигур пуст. Попробуйте сначала заполнить массив, чтобы удалить объект" << endl;
        return;
    }

    int index;
    cout << "Введите номер фигуры для удаления: ";
    cin >> index;
    index--;

    if (index < 0 || index >= figures->size()) {
        cout << "Такой фигуры нет. Попробуйте ввести коректный номер фигуры";
        return;
    }

    deleteClass(figures, index);
}

vector<int> getIndexes(vector<Figure*> figures, int area) {
    vector<int> indexes;
    for (int i = 0; i < figures.size(); i++) {
        if (figures[i]->getArea() > area) {
            indexes.push_back(i);
        }
    }
    return indexes;
}

void deletePerArea(vector<Figure*>* figures) {
    if (figures->empty()) {
        cout << "Массив фигур пуст. Попробуйте сначала заполнить массив, чтобы удалить объект" << endl;
        return;
    }

    int area;
    cout << "Фигуры большие этой площадь удаляться. Введите площадь: ";
    cin >> area;

    if (area <= 0) {
        cout << "Площадь не может быть отрицательной. Попробуйте ввести коректную площадь";
        return;
    }

    vector<int> indexes = getIndexes(*figures, area);
    if (indexes.empty()) {
        cout << "Таких объектов нет. Попробуйте ввести другую площадь." << endl;
        return;
    }

    for (int i = 0; i < indexes.size(); i++) {
        deleteClass(figures, indexes[i]);
    }
}