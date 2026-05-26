#include <iostream>

#include "./interface/mainwindow.h"

#include <QApplication>

#include "interface/qtscene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Scene scene;
    FileReader reader;
    Facade facade(reader, scene);

    MainWindow w(facade);
    w.setWindowTitle("3D Graphics");
    w.show();
    return a.exec();
}
