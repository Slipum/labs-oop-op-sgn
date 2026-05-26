#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "facade.h"
#include "graphics/visual.h"

#define MIN_WIDTH 400
#define MIN_HEIGHT 600

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool animation = false;
    Facade _facade;

public:
    explicit MainWindow(Facade& facade, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;

    void setupStyles();

    void updateSlider(VisualWidget *visual);
    void findClicked();

    void normalize();
    void setAnimation();

    void infoClicked();
};
#endif // MAINWINDOW_H
