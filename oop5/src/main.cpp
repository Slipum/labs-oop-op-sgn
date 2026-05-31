#include <iostream>

#include "interface/mainwindow.h"
#include <QApplication>

#include "abstructs/builder/builder.h"


int main(int argc, char *argv[]) {
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.setWindowTitle("Simulator elevator");
    // w.show();
    // return a.exec();
    ElevatorBuilder elevatorBuilder;
    auto elevator = elevatorBuilder.createElevator(10);
    std::cout << elevator->getFloor() << std::endl << std::endl;
    elevator->setFloor(4);
    std::cout << elevator->getController()->getFloor() << std::endl;

    return 0;
}
