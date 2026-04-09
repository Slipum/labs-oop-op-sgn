#include "mainwindow.h"
#include "entrypoint/entrypoint.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QLineEdit* output = ui->outputLine;
    output->setReadOnly(true);
    output->setToolTip("Поле нельзя именить. Здесь будет выведен результат конвертера.");

    connect(ui->convertBtn, &QPushButton::clicked, this, &MainWindow::convertBtnClick);
    connect(ui->inputLine, &QLineEdit::cursorPositionChanged, this, &MainWindow::onInputChange);
    connect(ui->copyBtn, &QPushButton::clicked, this, &MainWindow::copy);
    connect(ui->inputLine, &QLineEdit::returnPressed, this, &MainWindow::pressReturn);
    connect(ui->changeValues, &QPushButton::clicked, this, &MainWindow::onChangeValue);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::convertBtnClick() {
    updateContext();

    doConvert(&context);

    ui->outputLine->setText(context.input);
    ui->errorLabel->setText("");
}

void MainWindow::updateContext() {
    QByteArray inputTemp = ui->inputLine->text().toUtf8();
    context.input = (char*)malloc(inputTemp.size() + 1);
    strcpy(context.input, inputTemp.constData());

    context.inputSys = ui->inputBox->currentText().toInt();
    context.outputSys = ui->outputBox->currentText().toInt();
}


void MainWindow::onInputChange() {
    if (ui->inputLine->text() != "") {
        updateContext();

        doConvert(&context);
        isCorrect();

        updateLabels();
    } else {
        ui->errorLabel->setText("");
    }
}

void MainWindow::copy() {
    if (ui->inputLine->text() != "") {
        ui->inputLine->selectAll();
        ui->inputLine->copy();
        ui->inputLine->deselect();
        ui->errorLabel->setStyleSheet("color: rgb(85, 183, 69);");
        ui->errorLabel->setText("Успешно скопировалось!");
    } else {
        ui->errorLabel->setStyleSheet("color: rgb(183, 49, 41);");
        ui->errorLabel->setText("Извините, поле пустое и нечего копировать.\nПопробуйте сначала его заполнить.");
    }
}

void MainWindow::pressReturn() {
    if (ui->convertBtn->isEnabled()) {
        convertBtnClick();
    }
}

void MainWindow::onChangeValue() {
    if (ui->convertBtn->isEnabled() && ui->inputLine->text() != "") {
        QString tempBox = ui->inputBox->currentText();
        ui->inputBox->setCurrentText(ui->outputBox->currentText());
        ui->outputBox->setCurrentText(tempBox);

        QString tempLine = ui->inputLine->text();
        ui->inputLine->setText(ui->outputLine->text());
        ui->outputLine->setText(tempLine);
    }
}

void MainWindow::isCorrect() {
    if (!context.error) {
        ui->convertBtn->setEnabled(true);
        ui->convertBtn->setStyleSheet("background-color: rgb(189, 91, 12);\ncolor: rgb(255, 255, 255);");
    } else {
        ui->convertBtn->setEnabled(false);
        ui->convertBtn->setStyleSheet("background-color: rgb(74, 74, 74);\ncolor: rgb(255, 255, 255);");
    }
}

void MainWindow::updateLabels() {
    if (context.error) {
        ui->outputLine->setText("");
        ui->errorLabel->setStyleSheet("color: rgb(183, 49, 41);");
        ui->errorLabel->setText(context.input);
    } else {
        ui->errorLabel->setText("");
    }
}
