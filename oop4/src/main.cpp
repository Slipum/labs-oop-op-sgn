#include <iostream>

#include "./interface/mainwindow.h"

#include <QApplication>

#include "facade.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("3D Graphics");
    w.show();
    return a.exec();
}
