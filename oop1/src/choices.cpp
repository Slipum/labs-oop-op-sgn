#include "choices.h"
#include "stdfree.h"
#include "validEnd.h"
#include <iostream>

void Choices::printFigureTypes() {
    cout << "1. Круг" << endl;
    cout << "2. Прямоугольник" << endl;
    cout << "3. Треугольник" << endl;
    cout << "4. Выпуклый многоугольник" << endl;
}

void Choices::setNameFigure(Figure* f) {
    string name;
    do {
        cout << "Введите имя: ";
        getline(cin, name, '\n');
    } while (!f->setName(name));
}

void Choices::addRectangle(vector<Figure*>* figures) {
    Rectangle* f = new Rectangle();
    this->setNameFigure(f);
    bool valid = true;

    coord l;
    do {
        valid = true;
        cout << "Введите координаты левого верхнего угла: ";
        cin >> l.x >> l.y;
        if (cin.fail() || !validEnd(cin.peek())) {
            cout << "Введите обе координаты левого верхнего угла." << endl;
            freeInput();
            valid = false;
            continue;
        }
    } while (!f->setLeftCorner(l.x, l.y, cin.fail()) || !valid);

    if (valid) {
        coord r;
        do {
            valid = true;
            cout << "Введите координаты правого нижнего угла: ";
            cin >> r.x >> r.y;
            if (cin.fail() || !validEnd(cin.peek())) {
                cout << "Введите обе координаты правого нижнего угла." << endl;
                freeInput();
                valid = false;
                continue;
            }
        } while (!f->setRightCorner(r.x, r.y, cin.fail()) || !valid);
    }
    if (valid) figures->push_back(f);
}

bool Choices::setTriangleCorner(Triangle* f, string corner) {
    coord c;
    bool success;
    bool valid = true;
    do {
        valid = true;
        cout << "Введите координаты " << corner << " угла: ";
        cin >> c.x >> c.y;
        if (cin.fail() || !validEnd(cin.peek())) {
            cout << "Введите обе координаты " << corner << " угла." << endl;
            freeInput();
            valid = false;
            continue;
        }

        if (corner == "первого") {
            success = f->setA(c.x, c.y, cin.fail());
        } else if (corner == "второго") {
            success = f->setB(c.x, c.y, cin.fail());
        } else {
            success = f->setC(c.x, c.y, cin.fail());
        }
    } while (!success || !valid);
    return valid;
}

void Choices::setPolygonCorner(vector<coord>* corners, string corner) {
    coord c;

    cout << "Введите координаты " << corner << " угла: ";
    cin >> c.x >> c.y;
    while (cin.fail()) {
        cout << "Введите обе координаты " << corner << " угла." << endl;
        freeInput();
        cout << "Введите координаты " << corner << " угла: ";
        cin >> c.x >> c.y;
    };
    corners->push_back(c);
}

void Choices::addTriangle(vector<Figure*>* figures) {
    Triangle* f = new Triangle();
    this->setNameFigure(f);

    this->setTriangleCorner(f, "первого");
    this->setTriangleCorner(f, "второго");
    this->setTriangleCorner(f, "третьего");

    figures->push_back(f);
}

void Choices::addPolygon(vector<Figure*>* figures) {
    Polygon* f = new Polygon();
    this->setNameFigure(f);
    bool valid = true;

    int corns;
    cout << "Введите количество вершин: ";
    cin >> corns;
    while (cin.fail() || corns <= 0) {
        valid = true;
        cout << "Некоректное количество вершин." << endl;
        cout << "Введите количество вершин: ";
        freeInput();
        cin >> corns;
        if (!validEnd(cin.peek())) {
            valid = false;
        }
    }

    vector<coord> corners;
    for (int i = 1; i < corns+1; i++) {
        this->setPolygonCorner(&corners, (to_string(i) + "-ого"));
    }
    f->setCorners(corners);

    figures->push_back(f);
}

void Choices::addCircle(vector<Figure*>* figures) {
    Circle* f = new Circle();
    this->setNameFigure(f);
    bool valid = true;

    coord c;
    do {
        valid = true;
        cout << "Введите координаты центра: ";
        cin >> c.x >> c.y;
        if (cin.fail()) {
            cout << "Введите обе координаты центра." << endl;
            freeInput();
            valid = false;
            continue;
        }
    } while (!f->setCenter(c.x, c.y, cin.fail()) || !valid);
    freeInput();

    if (valid) {
        float r;
        do {
            valid = true;
            cout << "Введите радиус: ";
            cin >> r;
            if (!validEnd(cin.peek())) {
                freeInput();
                r = NULL;
                valid = false;
                continue;
            }
        } while (!f->setRadius(r));
    }
    if (valid) figures->push_back(f);
}

void Choices::deleteClass(vector<Figure*>* arr, int index) {
    delete (*arr)[index];
    arr->erase(arr->begin() + index);
}

vector<int> Choices::getIndexes(vector<Figure*> figures, int area) {
    vector<int> indexes;
    for (size_t i = 0; i < figures.size(); i++) {
        if (figures[i]->getArea() > area) {
            indexes.push_back(i);
        }
    }
    return indexes;
}

int Choices::addFigure(vector<Figure*>* figures) {
    int typeFigure;
    this->printFigureTypes();
    cout << "Введите тип фигуры: ";
    cin >> typeFigure;
    if (!validEnd(cin.peek())) {
        typeFigure = ERROR;
    }
    freeInput();
    switch (typeFigure) {
    case CIRCLE: {
        this->addCircle(figures);
        break;
    }
    case RECTANGLE: {
        this->addRectangle(figures);
        break;
    }
    case TRIANGLE: {
        this->addTriangle(figures);
        break;
    }
    case POLYGON: {
        this->addPolygon(figures);
        break;
    }
    default: {
        cout << "Некорректный пункт. Попробуйте другой из предложенных:" << endl;
        break;
    }
    }
    return typeFigure;
}

void Choices::printAllParams(vector<Figure*> figures) {
    if (figures.size() == 0) {
        cout << "Массив фигур пуст. Попробуйте сначала добавить фигуру." << endl;
        return;
    }
    for (size_t i = 0; i < figures.size(); i++) {
        cout << "[" << i + 1 << "] ";
        figures[i]->printParam();
    }
}

void Choices::printAllAreas(vector<Figure*> figures) {
    if (figures.size() == 0) {
        cout << "Массив фигур пуст. Попробуйте сначала добавить фигуру." << endl;
        return;
    }
    for (size_t i = 0; i < figures.size(); i++) {
        cout << "[" << i + 1 << "] ";
        figures[i]->printArea();
    }
}

void Choices::sumAreas(vector<Figure*> figures) {
    double sum = 0;
    for (size_t i = 0; i < figures.size(); i++) {
        sum += figures[i]->getArea();
    }
    cout << "Сумма площадей всех фигур: " << sum << endl;
}

void Choices::sortByArea(vector<Figure*>* figures) {
    sort(figures->begin(), figures->end(), this->compare);
    cout << "Фигуры отсортированы по площади (по возрастанию)" << endl;
}

void Choices::deletePerNum(vector<Figure*>* figures) {
    if (figures->empty()) {
        cout << "Массив фигур пуст. Попробуйте сначала заполнить массив, чтобы удалить объект" << endl;
        return;
    }

    int index;
    cout << "Введите номер фигуры для удаления: ";
    cin >> index;
    index--;

    if (index < 0 || index >= int(figures->size())) {
        cout << "Такой фигуры нет. Попробуйте ввести коректный номер фигуры" << endl;
        return;
    }

    this->deleteClass(figures, index);
}

void Choices::deletePerArea(vector<Figure*>* figures) {
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

    for (size_t i = 0; i < indexes.size(); i++) {
        this->deleteClass(figures, indexes[i]);
    }
}