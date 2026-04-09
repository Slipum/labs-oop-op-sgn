#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFont>
#include <QMessageBox>
#include <QStringList>
#include <string.h>

#include "../entrypoint/entrypoint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadingDialog = nullptr;
    ui->outputMetrics->setReadOnly(true);
    ui->regionBox->setEnabled(false);
    ui->columeBox->setEnabled(false);
    ui->inputFileName->setReadOnly(true);
    ui->loadData->setEnabled(false);

    connect(ui->findFile, &QPushButton::clicked, this, &MainWindow::findFileClicked);
    connect(ui->loadData, &QPushButton::clicked, this, &MainWindow::getData);
    connect(ui->calculateMetrics, &QPushButton::clicked, this, &MainWindow::calculateMetrics);
}

MainWindow::~MainWindow()
{
    freeContext();
    if (context.region) free(context.region);
    if (context.regions) free(context.regions);
    if (context.filePath) free(context.filePath);
    if (context.metrics) free(context.metrics);
    delete ui;
}

void MainWindow::freeContext() {
    if (context.outputMetrics) {
        for (int i = 0; i < context.rows; i++) if (context.outputMetrics[i]) freeRow(context.outputMetrics[i]);
        free(context.outputMetrics);
        context.outputMetrics = nullptr;
    }
}

void MainWindow::findFileClicked() {
    updateContext();

    ui->regionBox->setEnabled(true);
    ui->columeBox->setEnabled(true);
}

void MainWindow::updateContext() {
    QByteArray dialog = QFileDialog::getOpenFileName(this, tr("Open File"), "/Users/slipum/project/Qt-projects/labs/op2", tr("CSV files (*.csv)")).toUtf8();
    context.filePath = (char*)malloc(dialog.size() + 1);
    strcpy(context.filePath, dialog.constData());

    ui->inputFileName->setText(context.filePath);
    ui->loadData->setEnabled(true);
}


void MainWindow::getData() {
    freeContext();
    showLoadingDialog();
    loadRegion();
    doCreateTable(&context, LOAD);
    QStringList regionsList(context.regions, context.regions + context.uniqueRegionCount);
    ui->regionBox->addItems(regionsList);
    hideLoadingDialog();
    if (context.error == INVALID_FILE || context.error == INVALID_PATH || context.error == INVALID_REGION) {
        ui->table->clear();
        ui->table->setRowCount(0);
        ui->table->setColumnCount(0);
        createErrorWindow();
        return;
    }
    updateTable();
    createInfoWindow();
}

void MainWindow::updateTable() {
    ui->table->clear();
    ui->table->setRowCount(0);

    setTable();

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    updateFontTable();
}

void MainWindow::setTable() {
    ui->table->setColumnCount(COLS_COUNT);
    QStringList headers({"Year", "Region", "Population", "Birth rate", "Death rate","Demographic", "Urbanization"});
    ui->table->setHorizontalHeaderLabels(headers);
    ui->table->setRowCount(context.rows);

    for (int row = 0; row < context.rows; ++row) {
        Row* currentRow = context.outputMetrics[row];
        for (int column = 0; column < COLS_COUNT; column++) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromUtf8(getColumnName(currentRow, column)));
            ui->table->setItem(row, column, item);
        }
    }
}

char* MainWindow::getColumnName(Row* row, int column) {
    switch (column) {
    case YEAR: return row->year;
    case REGION: return row->region;
    case POPULATION: return row->population;
    case BIRTH_RATE: return row->birth_rate;
    case DEATH_RATE: return row->death_rate;
    case DEMOGRAPHIC: return row->demographic;
    case URBANIZATION: return row->urbanization;
    default: return nullptr;
    }
}

void MainWindow::updateFontTable() {
    QFont header= ui->table->horizontalHeader()->font();
    header.setPointSize(25);
    ui->table->horizontalHeader()->setFont(header);

    QFont numFont = ui->table->verticalHeader()->font();
    numFont.setPointSize(25);
    ui->table->verticalHeader()->setFont(numFont);
}

void MainWindow::loadRegion() {
    if (ui->regionBox->count() == 0) return;
    QByteArray region = ui->regionBox->currentText().toUtf8();
    context.region = (char*)malloc(region.size() + 1);
    strcpy(context.region, region.constData());
}

void MainWindow::freeRow(Row* row) {
    if (!row) return;
    if (row->year) free(row->year);
    if (row->region) free(row->region);
    if (row->population) free(row->population);
    if (row->birth_rate) free(row->birth_rate);
    if (row->death_rate) free(row->death_rate);
    if (row->demographic) free(row->demographic);
    if (row->urbanization) free(row->urbanization);
    free(row);
    row = nullptr;
}

void MainWindow::createInfoWindow() {
    QMessageBox info(this);
    info.setWindowTitle("Load information");
    QString str = QString("Load rows: %2\nError rows: %3\nValid rows: %1").arg(context.rows).arg(context.realRows).arg(context.realRows - context.rows);
    info.setText(QString::fromUtf8(str.toUtf8()));
    info.setStyleSheet(
        "QMessageBox {"
        "    background-color: #2b2b2b;"
        "}"
        "QLabel {"
        "    color: rgb(255, 255, 255);"
        "    background-color: #2b2b2b;"
        "    font-size: 20px;"
        "}"
    );
    info.exec();
}

void MainWindow::createErrorWindow() {
    QMessageBox info(this);
    info.setWindowTitle("Error");
    switch (context.error) {
        case INVALID_PATH:  info.setText("Invalid path"); break;
        case INVALID_COLUMN: ui->outputMetrics->setText(""); info.setText("Invalid column"); break;
        case INVALID_REGION: ui->outputMetrics->setText(""); info.setText("Invalid region"); break;
        case INVALID_FILE: ui->outputMetrics->setText(""); info.setText("Invalid file"); break;
    }
    info.setStyleSheet(
        "QMessageBox {"
        "    background-color: #2b2b2b;"
        "}"
        "QLabel {"
        "    color: #fc032c;"
        "    background-color: #2b2b2b;"
        "    font-size: 30px;"
        "}"
    );
    info.exec();

    context.error = 0;
}

void MainWindow::calculateMetrics() {
    if (context.filePath == nullptr) {
        context.error = INVALID_PATH;
        createErrorWindow();
        return;
    }
    getMetrics();
    freeContext();
    loadRegion();
    showLoadingDialog();
    doCreateTable(&context, METRICS);
    hideLoadingDialog();
    if (context.error) {
        createErrorWindow();
        return;
    }
    updateTable();

    if (context.metrics) createMetricsWindow();
}

void MainWindow::createMetricsWindow() {
    QMessageBox metrics(this);
    metrics.setWindowTitle("Metrics");
    QString str = QString("Minimum: %1\nMaximum: %2\nMediana: %3")
        .arg(context.metrics[MINIMUM])
        .arg(context.metrics[MAXIMUM])
        .arg(context.metrics[MEDIANA]);
    ui->outputMetrics->setText(str);
    metrics.setText(QString::fromUtf8(str.toUtf8()));
    metrics.setStyleSheet(
        "QMessageBox {"
        "    background-color: #2b2b2b;"
        "}"
        "QLabel {"
        "    color: rgb(255, 255, 255);"
        "    background-color: #2b2b2b;"
        "    font-size: 20px;"
        "}"
    );
    metrics.exec();
}

void MainWindow::showLoadingDialog() {
    if (loadingDialog) return;

    loadingDialog = new QProgressDialog("Загрузка данных...", nullptr, 0, 0, this);
    loadingDialog->setWindowTitle("Пожалуйста, подождите");
    loadingDialog->setWindowModality(Qt::WindowModal);
    loadingDialog->setMinimumDuration(0);
    loadingDialog->setCancelButton(nullptr);
    loadingDialog->show();
}

void MainWindow::hideLoadingDialog() {
    if (loadingDialog) {
        loadingDialog->close();
        loadingDialog->deleteLater();
        loadingDialog = nullptr;
    }
}

void MainWindow::getMetrics() {
    context.colum = ui->columeBox->currentIndex();
    if (context.colum != YEAR) context.colum++;
    if (context.colum == REGION || context.colum > URBANIZATION || context.colum < YEAR) context.error = INVALID_COLUMN;
};