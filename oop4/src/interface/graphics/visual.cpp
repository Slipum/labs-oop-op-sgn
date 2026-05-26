#include "visual.h"

#include <QTimer>

VisualWidget::VisualWidget(Facade* facade, bool& animation, QWidget *parent)
    : QWidget(parent), _animation(animation)
{
    float FPS = 60.0f;
    float dt = 1 / FPS;
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this, facade] {
        facade->DrawScene();
        update();
    });
    timer->start(1000.0f/FPS);
}

void VisualWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}