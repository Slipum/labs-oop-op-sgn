#include <QApplication>
#include <QPushButton>
#include <QMainWindow>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    // QPushButton button("Hello world!", nullptr);
    // button.resize(200, 100);
    // button.show();

    QMainWindow main;
    main.show();

    return a.exec();
}