#include <iostream>

#include "interface/mainwindow.h"
#include <QApplication>

#include "facade.h"


int main(int argc, char *argv[]) {
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.setWindowTitle("Simulator elevator");
    // w.show();
    // return a.exec();
    ElevatorFacade facade(10);

    facade.AcceptFromCabin(5);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    facade.AcceptFromCabin(3);
    facade.AcceptFromCabin(2);
    facade.AcceptFromCabin(7);
    facade.AcceptFromCabin(6);

    return 0;
}
