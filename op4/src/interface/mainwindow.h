#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../entrypoint/appcontex.h"
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
    AppContext context;
    int animation = 0;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;

    void resetClicked();

    void setupStyles();

    void updateSlider(VisualWidget *visual);
    void findClicked();
    void getError(Errors error);

    void normalize();
    void setAnimation();

    void infoClicked();
};
#endif // MAINWINDOW_H
