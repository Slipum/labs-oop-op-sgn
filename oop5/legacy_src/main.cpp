#include "interface/mainwindow.h"
#include <QApplication>

#include "abstructs/builder.h"


int main(int argc, char *argv[]) {
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.setWindowTitle("Simulator elevator");
    // w.show();
    // return a.exec();

    ElevatorBuilder builder;
    builder.createElevator();
    return 0;
}
