#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QPushButton>

#include "entrypoint/entrypoint.h"
#include "texts.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _moveTimer(this),
      _waitTimer(this),
      _doorOpenTimer(this),
      _doorCloseTimer(this) {
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    _rowFloors[1] = ui->rowFloor1;
    _rowFloors[2] = ui->rowFloor2;
    _rowFloors[3] = ui->rowFloor3;
    _rowFloors[4] = ui->rowFloor4;
    _rowFloors[5] = ui->rowFloor5;

    _floorLamps[1] = ui->floorLamp1;
    _floorLamps[2] = ui->floorLamp2;
    _floorLamps[3] = ui->floorLamp3;
    _floorLamps[4] = ui->floorLamp4;
    _floorLamps[5] = ui->floorLamp5;

    for (int floor = ElevatorConfig::MIN_FLOOR; floor <= ElevatorConfig::FLOOR_COUNT; ++floor) {
        _rowFloors[floor]->setProperty("rowRole", "floor");
        _floorLamps[floor]->setStyleSheet("background-color: #4a5568; border-radius: 6px;");
    }

    _moveTimer.setSingleShot(true);
    _waitTimer.setSingleShot(true);
    _doorOpenTimer.setSingleShot(true);
    _doorCloseTimer.setSingleShot(true);

    setupStyle();
    setupLogic();
    setupConnections();
    refreshUi();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupStyle() {
    setStyleSheet(QString::fromUtf8(R"(
    QMainWindow, QWidget {
        background-color: #1a1d23;
        color: #e8eaed;
        font-family: "Helvetica Neue";
        font-size: 20px;
    }
    QGroupBox {
        border: 1px solid #3d4450;
        border-radius: 10px;
        margin-top: 12px;
        padding: 12px 10px 10px 10px;
        font-weight: 600;
    }
    QGroupBox::title {
        subcontrol-origin: margin;
        left: 12px;
        padding: 0 6px;
        color: #9aa0a6;
    }
    QFrame#shaftFrame {
        background-color: #252a33;
        border-radius: 8px;
        border: 1px solid #3d4450;
    }
    QFrame[rowRole="floor"] {
        background-color: #2e3440;
        border-radius: 6px;
        padding: 4px;
    }
    QFrame[rowRole="floorActive"] {
        background-color: #1e4d7b;
        border: 1px solid #4a9eff;
        border-radius: 6px;
        padding: 4px;
    }
    QLabel#labelIndicator {
        background-color: #4a9eff;
        color: #ffffff;
        border-radius: 8px;
        padding: 10px;
        font-size: 15px;
        font-weight: 700;
    }
    QPushButton {
        background-color: #3d4450;
        border: none;
        border-radius: 8px;
        padding: 10px 14px;
        color: #e8eaed;
        font-weight: 600;
    }
    QPushButton:hover {
        background-color: #4a5568;
    }
    QPushButton:pressed {
        background-color: #4a9eff;
        color: #ffffff;
    }
    QPushButton#cabinFloor1, QPushButton#cabinFloor2, QPushButton#cabinFloor3,
    QPushButton#cabinFloor4, QPushButton#cabinFloor5 {
        font-size: 18px;
        min-width: 56px;
        min-height: 56px;
    }
    QLabel#hintLabel {
        color: #9aa0a6;
        font-size: 11px;
    }
    )"));
}

void MainWindow::setupLogic() {
    _facade.setStateChangedCallback([this]() { refreshUi(); });

    _facade.setTimerHost({
        [this](int ms) { _moveTimer.start(ms); },
        [this]() { _moveTimer.stop(); },
        [this](int ms) { _waitTimer.start(ms); },
        [this](int ms) { _doorOpenTimer.start(ms); },
        [this](int ms) { _doorCloseTimer.start(ms); },
    });
}

void MainWindow::setupConnections() {
    connect(ui->callFloor1, &QPushButton::clicked, this, &MainWindow::onCallFloor1);
    connect(ui->callFloor2, &QPushButton::clicked, this, &MainWindow::onCallFloor2);
    connect(ui->callFloor3, &QPushButton::clicked, this, &MainWindow::onCallFloor3);
    connect(ui->callFloor4, &QPushButton::clicked, this, &MainWindow::onCallFloor4);
    connect(ui->callFloor5, &QPushButton::clicked, this, &MainWindow::onCallFloor5);

    connect(ui->cabinFloor1, &QPushButton::clicked, this, &MainWindow::onCabinFloor1);
    connect(ui->cabinFloor2, &QPushButton::clicked, this, &MainWindow::onCabinFloor2);
    connect(ui->cabinFloor3, &QPushButton::clicked, this, &MainWindow::onCabinFloor3);
    connect(ui->cabinFloor4, &QPushButton::clicked, this, &MainWindow::onCabinFloor4);
    connect(ui->cabinFloor5, &QPushButton::clicked, this, &MainWindow::onCabinFloor5);

    connect(&_moveTimer, &QTimer::timeout, this, &MainWindow::onMoveTimer);
    connect(&_waitTimer, &QTimer::timeout, this, &MainWindow::onWaitTimer);
    connect(&_doorOpenTimer, &QTimer::timeout, this, &MainWindow::onDoorOpenTimer);
    connect(&_doorCloseTimer, &QTimer::timeout, this, &MainWindow::onDoorCloseTimer);
}

void MainWindow::refreshUi() {
    const auto &ctrl = _facade.elevator().controller();
    const int floor = ctrl.currentFloor();

    ui->labelCurrentFloor->setText(QStringLiteral("Текущий этаж: %1").arg(floor));
    ui->labelTarget->setText(QStringLiteral("Целевой этаж: %1").arg(ctrl.targetFloor()));
    ui->labelDirection->setText(QStringLiteral("Направление: %1").arg(direction(ctrl.direction())));
    ui->labelController->setText(QStringLiteral("Контроллер: %1").arg(controllerState(ctrl.state())));
    ui->labelCabin->setText(QStringLiteral("Кабина: %1").arg(cabinState(_facade.elevator().cabin().state())));
    ui->labelDoor->setText(QStringLiteral("Двери: %1").arg(doorState(_facade.elevator().door().state())));
    ui->labelPending->setText(QStringLiteral("Очередь: %1").arg(pendingFloors(ctrl.pendingFloors())));

    ui->labelIndicator->setText(QStringLiteral("Кабина: %1").arg(floor));
    highlightShaftFloor(floor);
}

void MainWindow::highlightShaftFloor(int floor) {
    for (int f = ElevatorConfig::MIN_FLOOR; f <= ElevatorConfig::FLOOR_COUNT; ++f) {
        const bool active = (f == floor);
        _rowFloors[f]->setProperty("rowRole", active ? "floorActive" : "floor");
        _rowFloors[f]->setStyleSheet(active ? QStringLiteral("background-color: #1e4d7b; border: 1px solid #4a9eff; border-radius: 6px;")
            : QStringLiteral("background-color: #2e3440; border-radius: 6px;"));
        _floorLamps[f]->setStyleSheet(active ?
            "background-color: #4a9eff; border-radius: 6px;"
            : "background-color: #4a5568; border-radius: 6px;");
    }
}

void MainWindow::onCallFloor1() { _facade.callFromFloor(1); }
void MainWindow::onCallFloor2() { _facade.callFromFloor(2); }
void MainWindow::onCallFloor3() { _facade.callFromFloor(3); }
void MainWindow::onCallFloor4() { _facade.callFromFloor(4); }
void MainWindow::onCallFloor5() { _facade.callFromFloor(5); }

void MainWindow::onCabinFloor1() { _facade.callFromCabin(1); }
void MainWindow::onCabinFloor2() { _facade.callFromCabin(2); }
void MainWindow::onCabinFloor3() { _facade.callFromCabin(3); }
void MainWindow::onCabinFloor4() { _facade.callFromCabin(4); }
void MainWindow::onCabinFloor5() { _facade.callFromCabin(5); }

void MainWindow::onMoveTimer() { _facade.onMove(); }
void MainWindow::onWaitTimer() { _facade.onWait(); }
void MainWindow::onDoorOpenTimer() { _facade.onDoorOpen(); }
void MainWindow::onDoorCloseTimer() { _facade.onDoorClose(); }
