#include "qtscene.h"

#include <algorithm>
#include <vector>

#include <QLineF>
#include <QPainter>

void QtSceneDrawer::DrawScene(const Scene& scene)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::white);

    QRectF rect = painter.viewport();
    auto viewMatrix = scene.GetCamera().GetViewMatrix();

    auto projectToPlane = [&](const Vertex& v) {
        const auto& p = v.GetPosition();
        auto cameraPoint = viewMatrix.TransformPoint(p);

        if (cameraPoint.z <= 0.1f) {
            return QPointF();
        }

        float focal = std::min(rect.width(), rect.height()) * 0.85f;
        return QPointF(
            rect.width() / 2.0f + cameraPoint.x * focal / cameraPoint.z,
            rect.height() / 2.0f - cameraPoint.y * focal / cameraPoint.z
        );
    };

    std::vector<QLineF> projectedEdges;

    for (const auto& fig : scene.GetFigures()) {
        for (const auto& edge : fig.GetEdges()) {
            if (!edge.GetBegin() || !edge.GetEnd()) {
                continue;
            }

            auto begin = viewMatrix.TransformPoint(edge.GetBegin()->GetPosition());
            auto end = viewMatrix.TransformPoint(edge.GetEnd()->GetPosition());

            if (begin.z <= 0.1f || end.z <= 0.1f) {
                continue;
            }

            QPointF a = projectToPlane(*edge.GetBegin());
            QPointF b = projectToPlane(*edge.GetEnd());

            projectedEdges.emplace_back(a, b);
        }
    }

    if (projectedEdges.empty()) {
        return;
    }

    painter.setPen(QPen(QColor(Qt::green), 1.4));

    for (const auto& edge : projectedEdges) {
        painter.drawLine(edge.p1(), edge.p2());
    }
}
