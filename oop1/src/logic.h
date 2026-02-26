#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <string>
#include <numbers>
#include <vector>
#include "stdfree.h"

using namespace std;

typedef struct {
    float x;
    float y;
} coord;

#define COUNT_COORDINATES 2

class Figure {
protected:
    string name;
public:
    bool setName(string a) {
        if (a == "") {
            cout << "Имя не может быть пустое. Попробуйте заполнить имя." << endl;
            return false;
        }
        name = a;
        return true;
    }

    string getName() {
        return name;
    }

    virtual float getArea() {
        return 0;
    }
    virtual void printParam() {}
    virtual void printArea() {}
};

class Circle : public Figure { // круг
private:
    float center[COUNT_COORDINATES];
    float radius;
public:
    bool setCenter(float x, float y, bool incorrectInput) {
        if (incorrectInput) {
            cout << "Введите обе координаты центра." << endl;
            freeInput();
            return false;
        }
        center[0] = x;
        center[1] = y;
        return true;
    }
    bool setRadius(float r) {
        if (r <= 0) {
            cout << "Введите коректное значение радиуса." << endl;
            freeInput();
            return false;
        }
        radius = r;
        return true;
    }

    float* getCenter() {
        return center;
    }
    float getRadius() {
        return radius;
    }

    float getArea() override {
        return numbers::pi * radius * radius;
    }

    void printParam() override {
        cout << "Тип: Круг" << " | Центр: " << center[0] << " " << center[1] << " | Радиус: " << radius << endl;
    }
    void printArea() override {
        cout << "Тип: Круг" << " | Площадь: " << this->getArea() << endl;
    }
};

class Rectangle : public Figure { // прямоугольник
private:
    float leftCorner[COUNT_COORDINATES]; // левый верхний
    float rightCorner[COUNT_COORDINATES]; // правый нижний
public:
    bool setLeftCorner(float x, float y, bool incorrectInput) {
        if (incorrectInput) {
            cout << "Введите обе координаты левого верхнего угла." << endl;
            freeInput();
            return false;
        }
        leftCorner[0] = x;
        leftCorner[1] = y;
        return true;
    }
    bool setRightCorner(float x, float y, bool incorrectInput) {
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
        rightCorner[0] = x;
        rightCorner[1] = y;
        return true;
    }

    float* getLeftCorner() {
        return leftCorner;
    }
    float* getRightCorner() {
        return rightCorner;
    }

    float getArea() override {
        return ((*rightCorner - *leftCorner) * (leftCorner[1] - rightCorner[1]));
    }

    void printParam() override {
        cout << "Тип: Прямоугольник" << " | Левый верхний угол: " << leftCorner[0] << " " << leftCorner[1] << " | Правый нижний угол: " << rightCorner[0] << " " << rightCorner[1] << endl;
    }
    void printArea() override {
        cout << "Тип: Прямоугольник" << " | Площадь: " << this->getArea() << endl;
    }
};

class Triangle : public Figure { // треугольник
private:
    float a[COUNT_COORDINATES];
    float b[COUNT_COORDINATES];
    float c[COUNT_COORDINATES];
public:
    bool setA(float x, float y, bool incorrectInput) {
        if (incorrectInput) {
            cout << "Введите обе координаты угла." << endl;
            freeInput();
            return false;
        }
        a[0] = x;
        a[1] = y;
        return true;
    }
    bool setB(float x, float y, bool incorrectInput) {
        if (incorrectInput) {
            cout << "Введите обе координаты угла." << endl;
            freeInput();
            return false;
        }
        b[0] = x;
        b[1] = y;
        return true;
    }
    bool setC(float x, float y, bool incorrectInput) {
        if (incorrectInput) {
            cout << "Введите обе координаты угла." << endl;
            freeInput();
            return false;
        }
        c[0] = x;
        c[1] = y;
        return true;
    }

    float* getA() {
        return a;
    }
    float* getB() {
        return b;
    }
    float* getC() {
        return c;
    }

    float getArea() override {
        return abs((*b - *a)*(c[1] - a[1]) - (*c - *a)*(b[1] - a[1]))/2;
    }

    void printParam() override {
        cout << "Тип: Треугольник" << " | Первая вершина: " << a[0] << " " << a[1] << " | Вторая вершина: " << b[0] << " " << b[1] << " | Третья вершина: " << c[0] << " " << c[1] << endl;
    }
    void printArea() override {
        cout << "Тип: Треугольник" << " | Площадь: " << this->getArea() << endl;
    }
};

class Polygon : public Figure { // выпуклый многоугольник
private:
    vector<coord> corners;
public:
    void setCorners(const vector<coord> corns) {
        corners = corns;
    }

    vector<coord> getCorners() {
        return corners;
    }

    float getArea() override {
        float a = 0, b = 0;
        for (int i = 0; i < corners.size()-1; i++) {
            a += corners[i].x * corners[i+1].y;
            b += corners[i].y * corners[i+1].x;
        }
        return abs(a-b)/2;
    }

    void printParam() override {
        cout << "Тип: Выпуклый многоугольник ";
        for (int i = 0; i < corners.size(); i++) {
            cout << "| {" << i+1 << "} вершина: "<< corners[i].x << " " << corners[i].y << " ";
        }
        cout << endl;
    }
    void printArea() override {
        cout << "Тип: Выпуклый многоугольник" << " | Площадь: " << this->getArea() << endl;
    }
};

void printFigureTypes();
void deleteClass(vector<Figure*>* arr, int index);
bool compare(Figure* a, Figure* b);
vector<int> getIndexes(vector<Figure*> figures, int area);
void setTriangleCorner(Triangle* f, string corner);
void setPolygonCorner(vector<coord>* corners, string corner);

void addCircle(vector<Figure*>* figures);
void addRectangle(vector<Figure*>* figures);
void addTriangle(vector<Figure*>* figures);
void addPolygon(vector<Figure*>* figures);

int addFigure(vector<Figure*>* figures);
void sortByArea(vector<Figure*>* figures);
void deletePerNum(vector<Figure*>* figures);
void deletePerArea(vector<Figure*>* figures);

void printAllParams(vector<Figure*> figures);
void printAllAreas(vector<Figure*> figures);
void sumAreas(vector<Figure*> figures);

enum FigureType {
    CIRCLE = 1,
    RECTANGLE,
    TRIANGLE,
    POLYGON,
};

#endif //LOGIC_H
