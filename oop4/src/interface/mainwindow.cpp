#include "mainwindow.h"

#include <algorithm>
#include <cmath>

#include "ui_mainwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLineEdit>
#include <QLocale>
#include <QMessageBox>
#include <QMouseEvent>
#include <QVBoxLayout>

MainWindow::MainWindow(Facade& facade, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _facade(facade)
{
    ui->setupUi(this);
    this->setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
    this->setFocusPolicy(Qt::StrongFocus);
    ui->inputRangeLeft->setEnabled(false);
    ui->inputRangeRight->setEnabled(false);

    _visual = new VisualWidget(_facade, animation, ui->visual);
    auto layout = new QVBoxLayout(ui->visual);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(_visual);
    _visual->setFocusPolicy(Qt::StrongFocus);

    ui->slider->setMinimum(1);
    ui->slider->setMaximum(10);
    ui->slider->setValue(1);
    ui->filePath->setEnabled(false);

    connect(ui->slider, &QSlider::valueChanged, this, [this]() {
        updateSlider();
        reloadScene();
    });

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::resetPosition);

    connect(ui->btnFind, &QPushButton::clicked, this, &MainWindow::findClicked);
    ui->filePath->installEventFilter(this);
    qApp->installEventFilter(this);

    connect(ui->inputRangeRight, &QLineEdit::editingFinished, this, &MainWindow::normalize);
    connect(ui->inputRangeLeft, &QLineEdit::editingFinished, this, &MainWindow::normalize);

    connect(ui->checkBox, &QCheckBox::toggled, this, &MainWindow::setAnimation);

    connect(ui->infoBtn, &QPushButton::clicked, this, &MainWindow::infoClicked);

    setupStyles();

    ui->filePath->setReadOnly(true);
    updateSlider();
}

void MainWindow::resetPosition() {
    if (ui->filePath->text().isEmpty()) return;

    ui->inputRangeLeft->clear();
    ui->inputRangeRight->clear();
    NormalizationParameters params;
    params.Max = 0;
    params.Min = 0;
    readNormalizationParameters(params);
    reloadScene();
}

void MainWindow::infoClicked() {
    QMessageBox::information(
        this,
        tr("Controls Guide"),
        tr(
            "Controls:\n\n"

            "Object movement relative to camera:\n"
            "W - move forward\n"
            "S - move backward\n"
            "A - move left\n"
            "D - move right\n"
            "Space - move up\n"
            "Shift - move down\n\n"

            "Object rotation:\n"
            "R / F - rotate around X axis\n"
            "X / C - rotate around Y axis\n"
            "Q / E - rotate around Z axis\n\n"
        )
    );
}

void MainWindow::setAnimation() {
    if (ui->checkBox->isChecked()) animation = true;
    else animation = false;
}

void MainWindow::normalize() {
    reloadScene();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress && obj == ui->filePath) {
        findClicked();
        return true;
    }

    if (event->type() == QEvent::KeyPress && !QApplication::activeModalWidget()) {
        if (qobject_cast<QLineEdit*>(QApplication::focusWidget())) {
            return QMainWindow::eventFilter(obj, event);
        }

        auto* keyEvent = static_cast<QKeyEvent*>(event);
        if (applyControlKey(keyEvent->key())) {
            return true;
        }
    }

    return QMainWindow::eventFilter(obj, event);
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

void MainWindow::updateSlider()
{
    ui->labelStep->setText("Step: " + QString::number(ui->slider->value()));
}

void MainWindow::findClicked() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"),"/Users/slipum/project/Qt-projects/labs/oop4",tr("CSV files (*.csv)"));


    _currentFilePath = path;
    reloadScene();
    ui->filePath->setText(path);
    ui->inputRangeLeft->clear();
    ui->inputRangeRight->clear();

    ui->inputRangeLeft->setEnabled(true);
    ui->inputRangeRight->setEnabled(true);
    _visual->setFocus();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (!applyControlKey(event->key())) {
        QMainWindow::keyPressEvent(event);
    }
}

bool MainWindow::applyControlKey(int key) {
    constexpr float rotStep = 10.0f * M_PI / 180.0f;
    constexpr float scaleUp = 1.1f;
    constexpr float scaleDown = 1.0f / scaleUp;
    // float moveStep = std::max(1, ui->slider->value());
    float moveStep = 10.0f;
    FacadeOperationResult result(true);

    switch (key) {
    case Qt::Key_W:
        result = _facade.MoveSceneRelative(0, moveStep);
        break;
    case Qt::Key_S:
        result = _facade.MoveSceneRelative(0, -moveStep);
        break;
    case Qt::Key_A:
        result = _facade.MoveSceneRelative(-moveStep, 0);
        break;
    case Qt::Key_D:
        result = _facade.MoveSceneRelative(moveStep, 0);
        break;
    case Qt::Key_Space:
        result = _facade.MoveSceneLocal(0, moveStep, 0);
        break;
    case Qt::Key_Shift:
        result = _facade.MoveSceneLocal(0, -moveStep, 0);
        break;
    case Qt::Key_R:
        result = _facade.RotateScene(rotStep, 0, 0);
        break;
    case Qt::Key_F:
        result = _facade.RotateScene(-rotStep, 0, 0);
        break;
    case Qt::Key_Q:
        result = _facade.RotateScene(0, -rotStep, 0);
        break;
    case Qt::Key_E:
        result = _facade.RotateScene(0, rotStep, 0);
        break;
    case Qt::Key_X:
        result = _facade.RotateScene(0, 0, rotStep);
        break;
    case Qt::Key_C:
        result = _facade.RotateScene(0, 0, -rotStep);
        break;
    default:
        return false;
    }

    if (!result.IsSuccess()) {
        QMessageBox::critical(this, "Error", result.GetErrorMessage().c_str());
    }

    updateVisualization();
    return true;
}

void MainWindow::readNormalizationParameters(NormalizationParameters& params)
{
    QString leftText = ui->inputRangeLeft->text().trimmed();
    QString rightText = ui->inputRangeRight->text().trimmed();

    if (leftText.isEmpty() && rightText.isEmpty()) {
        params.Min = 0.0f;
        params.Max = 0.0f;
        params.EnableNormalization = false;
        return;
    }

    bool leftOk = true;
    bool rightOk = true;

    int leftValue = 0;
    int rightValue = 0;

    if (!leftText.isEmpty()) {
        leftValue = leftText.toInt(&leftOk);
    }

    if (!rightText.isEmpty()) {
        rightValue = rightText.toInt(&rightOk);
    }

    if (!leftOk || !rightOk) {
        QMessageBox::warning(this, "Ошибка",
                             "Введите только числовые значения.");
        return;
    }

    params.Min = static_cast<float>(leftValue);
    params.Max = static_cast<float>(rightValue);
    params.EnableNormalization = true;
}

void MainWindow::reloadScene() {
    NormalizationParameters params;
    readNormalizationParameters(params);

    auto result = _facade.LoadScene(_currentFilePath.toStdString(), params);

    if (!result.IsSuccess()) {
        QMessageBox::critical(this, "Error", result.GetErrorMessage().c_str());
        return;
    }

    updateVisualization();
}

void MainWindow::updateVisualization() {
    if (_visual) {
        _visual->update();
    }
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
