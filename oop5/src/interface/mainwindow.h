#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QLabel>
#include <QMainWindow>
#include <QTimer>

#include "../facade.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onCallFloor1();
    void onCallFloor2();
    void onCallFloor3();
    void onCallFloor4();
    void onCallFloor5();
    void onCabinFloor1();
    void onCabinFloor2();
    void onCabinFloor3();
    void onCabinFloor4();
    void onCabinFloor5();
    void onMoveTimer();
    void onWaitTimer();
    void onDoorOpenTimer();
    void onDoorCloseTimer();

private:
    void setupLogic();
    void setupStyle();
    void setupConnections();
    void refreshUi();

    void highlightShaftFloor(int floor);

    Ui::MainWindow *ui = nullptr;
    ElevatorFacade _facade;

    QTimer _moveTimer;
    QTimer _waitTimer;
    QTimer _doorOpenTimer;
    QTimer _doorCloseTimer;

    QFrame *_rowFloors[6] = {};
    QLabel *_floorLamps[6] = {};
};

#endif // MAINWINDOW_H
