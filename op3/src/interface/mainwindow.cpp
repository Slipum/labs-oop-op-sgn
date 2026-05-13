#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFont>
#include <QMessageBox>
#include <QStringList>

#include "graphwindow.h"
#include "../entrypoint/entrypoint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadingDialog = nullptr;
    ui->regionBox->setEnabled(false);
    ui->columeBox->setEnabled(false);
    ui->inputFileName->setReadOnly(true);
    ui->createGraph->setEnabled(false);

    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->findFile, &QPushButton::clicked, this, &MainWindow::findFileClicked);
    connect(ui->createGraph, &QPushButton::clicked, this, &MainWindow::calculateMetrics);
}

MainWindow::~MainWindow()
{
    doOperation(&app, &context, FREE);
    if (app.region) free(app.region);
    if (app.filePath) free(app.filePath);
    delete ui;
}

void MainWindow::findFileClicked() {
    ui->regionBox->clear();

    ui->table->clear();
    ui->table->setRowCount(0);
    ui->table->setColumnCount(0);

    if (app.region) {
        free(app.region);
        app.region = nullptr;
    }
    updateParams();

    ui->regionBox->setEnabled(true);
    ui->columeBox->setEnabled(true);
    getData();
}

void MainWindow::updateParams() {
    QByteArray dialog = QFileDialog::getOpenFileName(this, tr("Open File"), "/Users/slipum/project/Qt-projects/labs/op2", tr("CSV files (*.csv)")).toUtf8();
    app.filePath = (char*)malloc(dialog.size() + 1);
    strcpy(app.filePath, dialog.constData());

    ui->inputFileName->setText(app.filePath);
    ui->createGraph->setEnabled(true);
}

void MainWindow::getData() {
    showLoadingDialog();
    loadRegion();
    doOperation(&app, &context, LOAD);
    updateRegionBox();
    hideLoadingDialog();
    if (context.error == INVALID_FILE || context.error == INVALID_PATH || context.error == INVALID_REGION || context.error == INVALID_CLOSE) {
        ui->table->clear();
        ui->table->setRowCount(0);
        ui->table->setColumnCount(0);
        createErrorWindow();
        return;
    }
    updateTable();
    createInfoWindow();
}

void MainWindow::updateRegionBox() {
    QString currentText = ui->regionBox->currentText();

    ui->regionBox->clear();

    QStringList regions(context.regions, context.regions + context.uniqueRegionCount);
    ui->regionBox->addItems(regions);

    int index = ui->regionBox->findText(currentText);
    if (index != -1) {
        ui->regionBox->setCurrentIndex(index);
    } else {
        ui->regionBox->setCurrentIndex(0);
    }
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
    app.region = (char*)malloc(region.size() + 1);
    strcpy(app.region, region.constData());
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
    if (context.error != INVALID_GRAPH) ui->regionBox->clear();
    switch (context.error) {
        case INVALID_PATH:  info.setText("Invalid path"); break;
        case INVALID_COLUMN: info.setText("Invalid column"); break;
        case INVALID_REGION: info.setText("Incorrect region"); break;
        case INVALID_GRAPH: info.setText("Such a region occurs only once"); break;
        case INVALID_FILE: info.setText("Invalid file"); break;
        case INVALID_CLOSE: info.setText("Error with close file"); break;
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

    doOperation(&app, &context, CLEAR_ERROR);
}

void MainWindow::calculateMetrics() {
    if (graph) {
        graph->close();
        graph->deleteLater();
        graph = nullptr;
    }
    getMetrics();
    loadRegion();
    showLoadingDialog();
    doOperation(&app, &context, METRICS);
    hideLoadingDialog();
    if (context.error) {
        createErrorWindow();
        return;
    }
    updateTable();

    graph = new GraphWindow(&context, &app);
    graph->show();
    // if (context.metrics) createMetricsWindow();
}

void MainWindow::createMetricsWindow() {
    QMessageBox metrics(this);
    metrics.setWindowTitle("Metrics");
    QString str = QString("Minimum: %1\nMaximum: %2\nMediana: %3")
        .arg(context.metrics[MINIMUM])
        .arg(context.metrics[MAXIMUM])
        .arg(context.metrics[MEDIANA]);
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
    app.colum = ui->columeBox->currentIndex();
};