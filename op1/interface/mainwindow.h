#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../entrypoint/app_context.h"

#define INIT_SIZE 128

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    AppContext context;

    void convertBtnClick();
    void onInputChange();
    void copy();
    void pressReturn();
    void onChangeValue();

    void updateContext();
    void isCorrect();
    void updateLabels();
};
#endif // MAINWINDOW_H
