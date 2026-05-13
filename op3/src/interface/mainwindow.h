#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>

#include "graphwindow.h"
#include "../entrypoint/appcontext.h"

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

private slots:
    void findFileClicked();
    void calculateMetrics();

private:
    Ui::MainWindow *ui;
    AppContext context;
    AppParams app;
    QProgressDialog* loadingDialog;
    GraphWindow* graph = nullptr;

    void createInfoWindow();
    void createErrorWindow();
    void createMetricsWindow();

    void getData();
    void showLoadingDialog();
    void hideLoadingDialog();

    void updateRegionBox();
    void updateParams();
    void loadRegion();
    void updateTable();
    void setTable();
    void updateFontTable();
    void freeRow(Row* row);
    char* getColumnName(Row* row, int column);
    void getMetrics();
};
#endif // MAINWINDOW_H
