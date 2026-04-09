#include "main.h"

#include "bussines/logic.h"

void MainFacade::test() {
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
    d->setCorners({{1, 1}, {1, 0}, {0, 1}});

    figures->push_back(a);
    figures->push_back(b);
    figures->push_back(c);
    figures->push_back(d);
}

void MainFacade::exec() {
    system("clear");
    MenuCommand command(figures);

    while (true) {
        try {
            command.exec();
        } catch (exception& e) {
            if (string(e.what()) == "EXIT")
                break;
            cout << e.what() << endl;
        }
    }

    for (size_t i = 0; i < figures->size(); i++) {
        delete figures->at(i);
    }
    figures->clear();
    system("clear");
}

int main() {
    MainFacade facade;
    facade.exec();
    return 0;
}

