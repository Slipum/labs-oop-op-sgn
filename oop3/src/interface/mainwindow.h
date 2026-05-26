#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../entrypoint/entrypoint.h"

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

    void initState();
    void connectBtns();

    void zeroClicked();
    void oneClicked();
    void twoClicked();
    void treeClicked();
    void fourClicked();
    void fiveClicked();
    void sixClicked();
    void sevenClicked();
    void eightClicked();
    void nineClicked();

    void dotClicked();

    void leftClicked();
    void rightClicked();

    void plusClicked();
    void minusClicked();
    void slashClicked();
    void multiClicked();

    void funcXClicked();

    void clear();
    void del();

    void updateLabels();
    void onUpdateClicked();

    bool endsWithOperator();
};
#endif // MAINWINDOW_H
