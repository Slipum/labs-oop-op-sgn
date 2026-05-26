#ifndef OOP4_VISUAL_H
#define OOP4_VISUAL_H

#include <QWidget>
#include <QPainter>
#include <QVector3D>

#include "../../entrypoint/appcontex.h"

class VisualWidget : public QWidget
{
    Q_OBJECT
    qreal t = 0;
    QTimer *timer;
    size_t size = 1;
    int* animation;

    AppContext *context;

public:
    explicit VisualWidget(AppContext *_context, int* _animation = nullptr, QWidget* parent = nullptr);
    void setSize(size_t _size);
    ~VisualWidget() = default;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void clear(const QBrush &fill);
    void point(QPointF p, const QBrush &fill, size_t size);
    QPointF screen(QPointF p);
    QPointF project(QVector3D p);
    void frame();
    void line(QPointF p1, QPointF p2);

    void setAnimation(int* _animation);
};

#endif //OOP4_VISUAL_H
