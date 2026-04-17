#include "interface/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Visualization graphs");
    w.show();
    return a.exec();
}
