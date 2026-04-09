#include "logic.h"

bool Figure::setName(string a) {
    if (a == "") {
        cout << "Имя не может быть пустое. Попробуйте заполнить имя." << endl;
        return false;
    }
    if (a[0] == ' ') {
        cout << "Строка начинается с пробела. Попробуйте заполнить корректное имя" << endl;
        return false;
    }
    name = a;
    return true;
}

bool Circle::setCenter(float x, float y, bool incorrectInput) {
    if (incorrectInput) {
        cout << "Введите обе координаты центра." << endl;
        freeInput();
        return false;
    }
    center[0] = x;
    center[1] = y;
    return true;
}

bool Circle::setRadius(float r) {
    if (r <= 0) {
        cout << "Введите коректное значение радиуса." << endl;
        freeInput();
        return false;
    }
    radius = r;
    return true;
}

bool Rectangle::setLeftCorner(float x, float y, bool incorrectInput) {
    if (incorrectInput) {
        cout << "Введите обе координаты левого верхнего угла.-" << endl;
        freeInput();
        return false;
    }
    leftCorner[0] = x;
    leftCorner[1] = y;
    return true;
}

bool Rectangle::setRightCorner(float x, float y, bool incorrectInput) {
    if (incorrectInput) {
        cout << "Введите обе координаты правого нижнего угла." << endl;
        freeInput();
        return false;
    }
    if (x < leftCorner[0] || y > leftCorner[1]) {
        cout << "Введите коректный правый нижний угл. Вероятно ваша правая нижняя координата левее(выше) левого верхнего угла." << endl;
        freeInput();
        return false;
    }
    if (abs(x - leftCorner[0]) < 1e-6 || abs(y - leftCorner[1]) < 1e-6) {
        cout << "Некорретная координата. Точки лежат на одной прямой" << endl;
        freeInput();
        return false;
    }
    rightCorner[0] = x;
    rightCorner[1] = y;
    return true;
}

bool Triangle::setA(float x, float y, bool incorrectInput) {
    if (incorrectInput) {
        cout << "Введите обе координаты угла." << endl;
        freeInput();
        return false;
    }
    a[0] = x;
    a[1] = y;
    return true;
}

bool Triangle::setB(float x, float y, bool incorrectInput) {
    if (incorrectInput) {
        cout << "Введите обе координаты угла." << endl;
        freeInput();
        return false;
    }
    if (a[0] == x && a[1] == y) {
        cout << "Некорретная координата. Точка совпадает с уже имеющейся" << endl;
        freeInput();
        return false;
    }
    b[0] = x;
    b[1] = y;
    return true;
}

bool Triangle::setC(float x, float y, bool incorrectInput) {
    if (incorrectInput) {
        cout << "Введите обе координаты угла." << endl;
        freeInput();
        return false;
    }
    c[0] = x;
    c[1] = y;
    if (this->getArea() < 1e-18) {
        cout << "Некорретная координата. Все точки лежат на одной прямой" << endl;
        freeInput();
        return false;
    }
    return true;
}

double Polygon::getArea() {
    double a = 0, b = 0;
    size_t n = corners.size();
    for (size_t i = 0; i < n; i++) {
        size_t next = (i + 1) % n;
        a += corners[i].x * corners[next].y;
        b += corners[i].y * corners[next].x;
    }
    return fabs(a - b) / 2.0;
}

void Polygon::printParam() {
    cout << "Тип: Выпуклый многоугольник ";
    for (size_t i = 0; i < corners.size(); i++) {
        cout << "| {" << i+1 << "} вершина: "<< corners[i].x << " " << corners[i].y << " ";
    }
    cout << endl;
}
