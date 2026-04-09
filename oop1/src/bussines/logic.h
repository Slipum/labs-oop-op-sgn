#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <string>
#include <numbers>
#include <vector>

#include "../commands/utils/utils.h"

using namespace std;

typedef struct {
    float x;
    float y;
} coord;

#define COUNT_COORDINATES 2

class Figure : public UtilsCommand {
protected:
    string name;
public:
    bool setName(string a);

    string getName() {
        return name;
    }

    virtual double getArea() {
        return 0;
    }

    virtual void printParam() {}
    virtual void printArea() {}

    virtual ~Figure() {
        cout << "Фигура удалена." << endl;
    }
};

class Circle : public Figure { // круг
private:
    float center[COUNT_COORDINATES];
    float radius;
public:
    bool setCenter(float x, float y, bool incorrectInput);
    bool setRadius(float r);

    float* getCenter() {
        return center;
    }
    float getRadius() {
        return radius;
    }

    double getArea() override {
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
    bool setLeftCorner(float x, float y, bool incorrectInput);
    bool setRightCorner(float x, float y, bool incorrectInput);

    float* getLeftCorner() {
        return leftCorner;
    }
    float* getRightCorner() {
        return rightCorner;
    }

    double getArea() override {
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
    bool setA(float x, float y, bool incorrectInput);
    bool setB(float x, float y, bool incorrectInput);
    bool setC(float x, float y, bool incorrectInput);

    float* getA() {
        return a;
    }
    float* getB() {
        return b;
    }
    float* getC() {
        return c;
    }

    double getArea() override {
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

    double getArea() override;

    void printParam() override;
    void printArea() override {
        cout << "Тип: Выпуклый многоугольник" << " | Площадь: " << this->getArea() << endl;
    }
};

#endif //LOGIC_H
