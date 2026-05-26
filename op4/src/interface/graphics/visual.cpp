#include "visual.h"

#include <iostream>
#include <QTimer>

#include "../../entrypoint/entrypoint.h"

VisualWidget::VisualWidget(AppContext *_context, int* _animation, QWidget *parent)
    : QWidget(parent), context(_context), animation(_animation)
{
    float FPS = 60.0f;
    float dt = 1 / FPS;
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this, dt, _animation] {
        if (*_animation == 1) doOperation(nullptr, context, Operation::ROTATE_ANIMATION, Type::PLACE);
        update();
    });
    timer->start(1000.0f/FPS);
}

void VisualWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    Q_UNUSED(event);

    frame();
}

void VisualWidget::clear(const QBrush &fill)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), fill);
}

void VisualWidget::point(QPointF p, const QBrush &fill, size_t size)
{
    QPainter painter(this);
    QRectF r(screen(p).x(),screen(p).y(), size, size);

    painter.setBrush(fill);
    painter.drawEllipse(r);
}

QPointF VisualWidget::screen(QPointF p)
{
    auto min = width() > height() ? height() : width();
    float x = ((width() - min) / 2) + ((p.x() + 1) / 2 * min);
    float y = ((height() - min) / 2) + ((1 - (p.y() + 1) / 2) * min);

    return QPointF(x, y);
}

QPointF VisualWidget::project(QVector3D p) {
    if (p.z() <= 0.0f) return QPointF(0,0);
    return QPointF((p.x() / p.z()), (p.y() / p.z()));
}

void VisualWidget::line(QPointF p1, QPointF p2)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::green, 0.5f));
    p1.setX(p1.x());
    p1.setY(p1.y());

    p2.setX(p2.x());
    p2.setY(p2.y());
    painter.drawLine(p1, p2);
}

void VisualWidget::frame()
{
    auto BACKGROUND = Qt::black;
    auto FOREGROUND = Qt::white;

    auto points = QVector<QVector3D>{};

    float cx = sqrt(context->count) / 2.0f;
    float cy = sqrt(context->count) / 2.0f;

    for (size_t i = 0; i < context->count; ++i) {
        float x = (context->points[i].x - cx) * size;
        float y = (context->points[i].y - cy) * size;

        points.append(QVector3D(
            x,
            y,
            context->points[i].z
        ));
    }

    auto lines = QVector<QVector<int>>{};

    for (size_t y = 0; y < sqrt(context->count) - 1; ++y) {
        for (size_t x = 0; x < sqrt(context->count) - 1; ++x) {
            int leftTop = y * sqrt(context->count) + x;
            int rightTop = y * sqrt(context->count) + (x + 1);
            int rightBottom = (y + 1) * sqrt(context->count) + (x + 1);
            int leftBottom = (y + 1) * sqrt(context->count) + x;

            lines.push_back(QVector<int>{leftTop, rightTop, rightBottom, leftBottom});
        }
    }

    clear(BACKGROUND);
    for (auto p : points) {
        if (p.z() > 0.0f) point(project(p), FOREGROUND, 1);
    }

    for (auto l : lines) {
        for (size_t i = 0; i < l.size(); ++i) {
            auto a = points[l[i]];
            auto b = points[l[(i+1) % l.size()]];
            if (a.z() > 0.0f && b.z() > 0.0f) line(
                screen(project(a)),
                screen(project(b))
            );
        }
    }
}

void VisualWidget::setSize(size_t _size)
{
    size = _size;
}