#include "mainwindow.h"

#include <iostream>

#include "../../build/Qt_6_9_2_for_macOS-Debug/ui_MainWindow.h"

#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QIntValidator>

MainWindow::MainWindow(Facade& facade, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _facade(facade)
{
    ui->setupUi(this);
    this->setMinimumSize(MIN_WIDTH, MIN_HEIGHT);

    ui->filePath->setEnabled(false);

    auto visual = new VisualWidget(_facade, animation);
    auto layout = new QVBoxLayout(ui->visual);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(visual);

    ui->slider->setMinimum(1);
    ui->slider->setMaximum(10);
    ui->slider->setValue(1);

    connect(ui->slider, &QSlider::sliderReleased, this, [this]() {});

    ui->inputRangeLeft->setValidator(new QIntValidator(this));
    ui->inputRangeRight->setValidator(new QIntValidator(this));

    connect(ui->btnFind, &QPushButton::clicked, this, &MainWindow::findClicked);
    ui->filePath->installEventFilter(this);
    connect(ui->inputRangeRight, &QLineEdit::editingFinished, this, &MainWindow::normalize);
    connect(ui->inputRangeLeft, &QLineEdit::editingFinished, this, &MainWindow::normalize);

    connect(ui->checkBox, &QCheckBox::stateChanged, this, &MainWindow::setAnimation);

    connect(ui->infoBtn, &QPushButton::clicked, this, &MainWindow::infoClicked);

    setupStyles();

    ui->filePath->setReadOnly(true);
}

void MainWindow::infoClicked() {
    QMessageBox::information(
        this,
        tr("Controls Guide"),
        tr(
            "Controls:\n\n"

            "Movement:\n"
            "W - move forward\n"
            "S - move backward\n"
            "A - move left\n"
            "D - move right\n"
            "Space - move up\n"
            "Shift - move down\n\n"

            "Rotation:\n"
            "R / F - rotate around X axis\n"
            "X / C - rotate around Y axis\n"
            "Q / E - rotate around Z axis"
        )
    );
}

void MainWindow::setAnimation() {
    if (ui->checkBox->isChecked()) animation = true;
    else animation = false;
}

void MainWindow::normalize() {
    if (ui->filePath->text().isEmpty() || ui->filePath->text().isEmpty()) return;

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress && obj == ui->filePath) {
        findClicked();
    }
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    QMainWindow::mousePressEvent(event);

    ui->inputRangeLeft->clearFocus();
    ui->inputRangeRight->clearFocus();
    ui->filePath->clearFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSlider(VisualWidget *visual)
{
    ui->labelStep->setText("Step: " + QString::number(ui->slider->value()));

}

void MainWindow::findClicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"),"/Users/slipum/project/Qt-projects/labs/oop4",tr("CSV files (*.csv)"));

    if (path.isEmpty())
        return;

    NormalizationParameters params{};

    auto result = _facade.LoadScene(path.toStdString(), params);

    if (!result.IsSuccess()) {
        QMessageBox::critical(this, "Error", result.GetErrorMessage().c_str());
        return;
    }

    ui->filePath->setText(path);
    ui->visual->update();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    constexpr float moveStep = 5.0f;
    constexpr float rotStep = 0.1f;

    switch (event->key()) {
    case Qt::Key_W:
        _facade.MoveScene(0, 0, -moveStep);
        break;
    case Qt::Key_S:
        _facade.MoveScene(0, 0, moveStep);
        break;
    case Qt::Key_A:
        _facade.MoveScene(-moveStep, 0, 0);
        break;
    case Qt::Key_D:
        _facade.MoveScene(moveStep, 0, 0);
        break;
    case Qt::Key_Space:
        _facade.MoveScene(0, moveStep, 0);
        break;
    case Qt::Key_Shift:
        _facade.MoveScene(0, -moveStep, 0);
        break;
    case Qt::Key_R:
        _facade.RotateScene(rotStep, 0, 0);
        break;
    case Qt::Key_F:
        _facade.RotateScene(-rotStep, 0, 0);
        break;
    case Qt::Key_Q:
        _facade.RotateScene(0, rotStep, 0);
        break;
    case Qt::Key_E:
        _facade.RotateScene(0, -rotStep, 0);
        break;
    case Qt::Key_X:
        _facade.RotateScene(0, 0, rotStep);
        break;
    case Qt::Key_C:
        _facade.RotateScene(0, 0, -rotStep);
        break;
    }

    update();
}

void MainWindow::setupStyles() {
    qApp->setStyleSheet(R"(
        QMainWindow {
            background-color: #1e1f22;
        }

        QWidget {
            background-color: #1e1f22;
            color: #f5f5f5;
            font-family: "Helvetica Neue";
        }

        QLabel {
            color: #ffffff;
            font-weight: 600;
            padding: 4px;
        }

        QLineEdit {
            background-color: #2b2d31;
            border: 2px solid #3c3f45;
            border-radius: 14px;
            padding: 12px 18px;
            color: white;
            selection-background-color: #4f8cff;
            font-size: 22px;
        }

        QLineEdit:focus {
            border: 2px solid #4f8cff;
            background-color: #32353b;
        }

        QLineEdit:hover {
            border: 2px solid #5d6169;
        }

        QPushButton {
            background-color: #4f8cff;
            border: none;
            border-radius: 16px;
            padding: 14px 22px;
            color: white;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #6ba1ff;
        }

        QPushButton:pressed {
            background-color: #3d73d1;
            padding-left: 24px;
            padding-top: 16px;
        }

        QSlider::groove:horizontal {
            border: none;
            height: 10px;
            background: #2b2d31;
            border-radius: 5px;
        }

        QSlider::sub-page:horizontal {
            background: #4f8cff;
            border-radius: 5px;
        }

        QSlider::handle:horizontal {
            background: white;
            width: 22px;
            height: 22px;
            margin: -7px 0;
            border-radius: 11px;
            border: 2px solid #4f8cff;
        }

        QSlider::handle:horizontal:hover {
            background: #dce8ff;
        }

        QWidget#visual {
            background-color: #25272c;
            border: 2px solid #3b3e45;
            border-radius: 20px;
        }

        QMenuBar {
            background-color: #2b2d31;
            color: white;
        }

        QMenuBar::item {
            background: transparent;
            padding: 8px 14px;
        }

        QMenuBar::item:selected {
            background: #4f8cff;
            border-radius: 8px;
        }

        QMenu {
            background-color: #2b2d31;
            border: 1px solid #3c3f45;
        }

        QMenu::item {
            padding: 8px 24px;
        }

        QMenu::item:selected {
            background-color: #4f8cff;
        }

        QCheckBox {
            color: #f5f5f5;
            spacing: 10px;
            font-size: 18px;
        }

        QCheckBox::indicator {
            width: 20px;
            height: 20px;
            border-radius: 6px;
            border: 2px solid #3c3f45;
            background-color: #2b2d31;
        }

        QCheckBox::indicator:hover {
            border: 2px solid #5d6169;
            background-color: #32353b;
        }

        QCheckBox::indicator:checked {
            background-color: #4f8cff;
            border: 2px solid #4f8cff;
        }

        QCheckBox::indicator:checked:hover {
            background-color: #6ba1ff;
            border: 2px solid #6ba1ff;
        }

        QCheckBox::indicator:pressed {
            background-color: #3d73d1;
        }

        QMessageBox {
            background-color: #1e1f22;
        }

        QMessageBox QLabel {
            color: #f5f5f5;
            font-size: 16px;
            font-weight: 500;
        }

        QMessageBox QPushButton {
            background-color: #4f8cff;
            border: none;
            border-radius: 12px;
            padding: 8px 16px;
            color: white;
            font-weight: bold;
            min-width: 80px;
        }

        QMessageBox QPushButton:hover {
            background-color: #6ba1ff;
        }

        QMessageBox QPushButton:pressed {
            background-color: #3d73d1;
        }
    )");

    ui->filePath->setPlaceholderText("Select file...");
    ui->inputRangeLeft->setPlaceholderText("From: (0)");
    ui->inputRangeRight->setPlaceholderText("To: (0)");
}
