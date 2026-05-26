#include <iostream>

#include "interface/mainwindow.h"

#include <QApplication>

#include "bussines/facade/facade.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Calculator");
    w.show();
    return a.exec();

    // CalcucateFacade application;
    // std::string input, output;
    // input = "1+2-15";
    // application.getCalculate(input, output);
    // std::cout << output << std::endl;
}
