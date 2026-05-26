#include "visual.h"

#include <QTimer>

#include "interface/qtscene.h"

// VisualWidget::VisualWidget(bool& animation, QWidget *parent)
//     : QWidget(parent), _animation(animation)
// {
//     float FPS = 60.0f;
//     float dt = 1 / FPS;
//     timer = new QTimer(this);
//
//     connect(timer, &QTimer::timeout, this, [this] {
//         update();
//     });
//     timer->start(1000.0f/FPS);
// }

VisualWidget::VisualWidget(Facade& facade, bool& animation, QWidget *parent)
    : QWidget(parent), _facade(facade), _animation(animation)
{
    float FPS = 60.0f;
    float dt = 1 / FPS;
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this] {
        update();
    });
    timer->start(1000.0f/FPS);
}

void VisualWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QtSceneDrawer drawer(painter);

    _facade.SetDrawer(&drawer);
    _facade.DrawScene();
}