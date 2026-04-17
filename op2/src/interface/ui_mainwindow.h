/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *labelColums;
    QLabel *labelRegion;
    QTableWidget *table;
    QPushButton *findFile;
    QLineEdit *inputFileName;
    QPushButton *calculateMetrics;
    QPushButton *loadData;
    QLineEdit *outputMetrics;
    QComboBox *columeBox;
    QComboBox *regionBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1247, 653);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(76, 76, 76);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        labelColums = new QLabel(centralwidget);
        labelColums->setObjectName("labelColums");
        QFont font;
        font.setPointSize(20);
        labelColums->setFont(font);
        labelColums->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(labelColums, 1, 1, 1, 1);

        labelRegion = new QLabel(centralwidget);
        labelRegion->setObjectName("labelRegion");
        labelRegion->setFont(font);
        labelRegion->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(labelRegion, 1, 0, 1, 1);

        table = new QTableWidget(centralwidget);
        table->setObjectName("table");
        QFont font1;
        font1.setPointSize(25);
        table->setFont(font1);
        table->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        gridLayout->addWidget(table, 6, 0, 1, 2);

        findFile = new QPushButton(centralwidget);
        findFile->setObjectName("findFile");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(findFile->sizePolicy().hasHeightForWidth());
        findFile->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(30);
        findFile->setFont(font2);
        findFile->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(125, 144, 163);"));

        gridLayout->addWidget(findFile, 0, 1, 1, 1);

        inputFileName = new QLineEdit(centralwidget);
        inputFileName->setObjectName("inputFileName");
        inputFileName->setFont(font2);
        inputFileName->setStyleSheet(QString::fromUtf8("background-color: rgb(30, 30, 30);"));

        gridLayout->addWidget(inputFileName, 0, 0, 1, 1);

        calculateMetrics = new QPushButton(centralwidget);
        calculateMetrics->setObjectName("calculateMetrics");
        calculateMetrics->setFont(font2);
        calculateMetrics->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(160, 92, 18);"));

        gridLayout->addWidget(calculateMetrics, 5, 1, 1, 1);

        loadData = new QPushButton(centralwidget);
        loadData->setObjectName("loadData");
        loadData->setFont(font2);
        loadData->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(86, 131, 83);"));

        gridLayout->addWidget(loadData, 4, 0, 1, 2);

        outputMetrics = new QLineEdit(centralwidget);
        outputMetrics->setObjectName("outputMetrics");
        outputMetrics->setFont(font2);
        outputMetrics->setStyleSheet(QString::fromUtf8("background-color: rgb(30, 30, 30);"));

        gridLayout->addWidget(outputMetrics, 5, 0, 1, 1);

        columeBox = new QComboBox(centralwidget);
        columeBox->addItem(QString());
        columeBox->addItem(QString());
        columeBox->addItem(QString());
        columeBox->addItem(QString());
        columeBox->addItem(QString());
        columeBox->addItem(QString());
        columeBox->setObjectName("columeBox");
        sizePolicy.setHeightForWidth(columeBox->sizePolicy().hasHeightForWidth());
        columeBox->setSizePolicy(sizePolicy);
        columeBox->setMinimumSize(QSize(0, 32));
        QFont font3;
        font3.setPointSize(30);
        font3.setBold(false);
        columeBox->setFont(font3);
        columeBox->setStyleSheet(QString::fromUtf8("background-color: rgb(30, 30, 30);\n"
"color: rgb(255, 255, 255);"));

        gridLayout->addWidget(columeBox, 2, 1, 1, 1);

        regionBox = new QComboBox(centralwidget);
        regionBox->addItem(QString());
        regionBox->setObjectName("regionBox");
        sizePolicy.setHeightForWidth(regionBox->sizePolicy().hasHeightForWidth());
        regionBox->setSizePolicy(sizePolicy);
        regionBox->setMaximumSize(QSize(16777215, 16777215));
        regionBox->setFont(font2);
        regionBox->setStyleSheet(QString::fromUtf8("background-color: rgb(30, 30, 30);\n"
"color: rgb(255, 255, 255);"));

        gridLayout->addWidget(regionBox, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1247, 34));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelColums->setText(QCoreApplication::translate("MainWindow", "Colum:", nullptr));
        labelRegion->setText(QCoreApplication::translate("MainWindow", "Name region:", nullptr));
        findFile->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        calculateMetrics->setText(QCoreApplication::translate("MainWindow", "Calculate metrics", nullptr));
        loadData->setText(QCoreApplication::translate("MainWindow", "Load data", nullptr));
        columeBox->setItemText(0, QCoreApplication::translate("MainWindow", "Year", nullptr));
        columeBox->setItemText(1, QCoreApplication::translate("MainWindow", "Population", nullptr));
        columeBox->setItemText(2, QCoreApplication::translate("MainWindow", "Birth rate", nullptr));
        columeBox->setItemText(3, QCoreApplication::translate("MainWindow", "Death rate", nullptr));
        columeBox->setItemText(4, QCoreApplication::translate("MainWindow", "Demographic", nullptr));
        columeBox->setItemText(5, QCoreApplication::translate("MainWindow", "Urbanization", nullptr));

        regionBox->setItemText(0, QString());

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
