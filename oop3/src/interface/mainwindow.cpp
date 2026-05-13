#include "mainwindow.h"
#include "../../build/Qt_6_9_2_for_macOS-Debug/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initState();

    connect(ui->clearBtn, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->delBtn, &QPushButton::clicked, this, &MainWindow::del);
    connectBtns();
    connect(ui->equalBtn, &QPushButton::clicked, this, &MainWindow::onUpdateClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectBtns() {
    connect(ui->zeroBtn, &QPushButton::clicked, this, &MainWindow::zeroClicked);
    connect(ui->oneBtn, &QPushButton::clicked, this, &MainWindow::oneClicked);
    connect(ui->twoBtn, &QPushButton::clicked, this, &MainWindow::twoClicked);
    connect(ui->treeBtn, &QPushButton::clicked, this, &MainWindow::treeClicked);
    connect(ui->fourBtn, &QPushButton::clicked, this, &MainWindow::fourClicked);
    connect(ui->fiveBtn, &QPushButton::clicked, this, &MainWindow::fiveClicked);
    connect(ui->sixBtn, &QPushButton::clicked, this, &MainWindow::sixClicked);
    connect(ui->sevenBtn, &QPushButton::clicked, this, &MainWindow::sevenClicked);
    connect(ui->eightBtn, &QPushButton::clicked, this, &MainWindow::eightClicked);
    connect(ui->nineBtn, &QPushButton::clicked, this, &MainWindow::nineClicked);

    connect(ui->dotBtn, &QPushButton::clicked, this, &MainWindow::dotClicked);

    connect(ui->leftBtn, &QPushButton::clicked, this, &MainWindow::leftClicked);
    connect(ui->rightBtn, &QPushButton::clicked, this, &MainWindow::rightClicked);

    connect(ui->slashBtn, &QPushButton::clicked, this, &MainWindow::slashClicked);
    connect(ui->minusBtn, &QPushButton::clicked, this, &MainWindow::minusClicked);
    connect(ui->plusBtn, &QPushButton::clicked, this, &MainWindow::plusClicked);
    connect(ui->multiBtn, &QPushButton::clicked, this, &MainWindow::multiClicked);
}

bool MainWindow::endsWithOperator() {
    QString text = ui->input->text();

    return text.endsWith("+")
           || text.endsWith("-")
           || text.endsWith("*")
           || text.endsWith("/");
}

void MainWindow::multiClicked() {
    if (!endsWithOperator() && !ui->input->text().isEmpty())
        ui->input->insert("*");
}

void MainWindow::plusClicked() {
    if (!endsWithOperator())
        ui->input->insert("+");
}

void MainWindow::minusClicked() {
    if (!endsWithOperator())
        ui->input->insert("-");
}

void MainWindow::slashClicked() {
    if (!endsWithOperator() && !ui->input->text().isEmpty())
        ui->input->insert("/");
}

void MainWindow::onUpdateClicked() {
    AppParams* param = new AppParams;
    param->input = ui->input->text().toStdString();
    doOperation(*param, context);

    updateLabels();
}

void MainWindow::updateLabels() {
    ui->output->setText(context.output.c_str());
}

void MainWindow::leftClicked() {
    ui->input->insert("(");
}

void MainWindow::rightClicked() {
    ui->input->insert(")");
}


void MainWindow::zeroClicked() {
    ui->input->insert("0");
}

void MainWindow::oneClicked() {
    ui->input->insert("1");
}

void MainWindow::twoClicked() {
    ui->input->insert("2");
}

void MainWindow::treeClicked() {
    ui->input->insert("3");
}

void MainWindow::fourClicked() {
    ui->input->insert("4");
}

void MainWindow::fiveClicked() {
    ui->input->insert("5");
}

void MainWindow::sixClicked() {
    ui->input->insert("6");
}

void MainWindow::sevenClicked() {
    ui->input->insert("7");
}
void MainWindow::eightClicked() {
    ui->input->insert("8");
}

void MainWindow::nineClicked() {
    ui->input->insert("9");
}

void MainWindow::dotClicked() {
    if (!ui->input->text().endsWith("."))
        ui->input->insert(".");
}

void MainWindow::clear() {
    ui->input->setText("");
    ui->output->setText("");
}

void MainWindow::del() {
    ui->input->backspace();
}

void MainWindow::initState() {
    ui->input->setReadOnly(true);
    ui->output->setReadOnly(true);
}