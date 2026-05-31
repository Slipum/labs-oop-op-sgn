#ifndef OOP4_VISUAL_H
#define OOP4_VISUAL_H

#include <QWidget>
#include <QPainter>

#include "facade.h"

class VisualWidget : public QWidget
{
    Q_OBJECT
    qreal t = 0;
    QTimer *timer;
    size_t size = 1;
    bool& _animation;
    Facade& _facade;

public:
    explicit VisualWidget(Facade& facade, bool& animation, QWidget* parent = nullptr);
    ~VisualWidget() = default;

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif //OOP4_VISUAL_H
