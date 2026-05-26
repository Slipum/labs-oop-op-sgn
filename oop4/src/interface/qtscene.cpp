#include "qtscene.h"
#include <QPainter>
void QtSceneDrawer::DrawScene(const Scene& scene)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::white);

    QRectF rect = painter.viewport(); // ← важно

    float centerX = rect.width() / 2.0f;
    float centerY = rect.height() / 2.0f;

    float scale = 20.0f;
    float cameraDistance = 10.0f;

    auto project = [&](const Vertex& v)
    {
        const auto& p = v.GetPosition();

        float factor = cameraDistance / (cameraDistance + p.z);

        return QPointF(
            p.x * factor * scale + centerX,
            p.y * factor * scale + centerY
        );
    };

    for (const auto& fig : scene.GetFigures())
    {
        for (const auto& edge : fig.GetEdges())
        {
            auto a = project(*edge.GetBegin());
            auto b = project(*edge.GetEnd());

            painter.drawLine(a, b);
        }
    }
}