#include <iostream>
#include "menu.h"
#include "logic.h"

void test(vector<Figure*>* figures) {
    Circle* a = new Circle();
    Rectangle* b = new Rectangle();
    Triangle* c = new Triangle();
    Polygon* d = new Polygon();

    a->setName("TEST_CIRCLE");
    a->setRadius(5);
    a->setCenter(1,1, false);

    b->setName("TEST_RECTANGLE");
    b->setLeftCorner(1,2, false);
    b->setRightCorner(2,1, false);

    c->setName("TEST_TRIANGLE");
    c->setA(0, 0, false);
    c->setB(1, 0, false);
    c->setC(0, 1, false);

    d->setName("TEST_POLYGON");
    d->setCorners({{0, 0}, {1, 0}, {0, 1}});

    figures->push_back(a);
    figures->push_back(b);
    figures->push_back(c);
    figures->push_back(d);
}

int main() {
    Menu menu;
    vector<Figure*> figures;
    // test(&figures);
    system("clear");
    while (menu.run(&figures) != EXIT) {}
    return 0;
}