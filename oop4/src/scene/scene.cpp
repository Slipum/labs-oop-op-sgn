#include "scene.h"

#include <QPainter>

#include "object/object.h"

void Scene::TransformFigures(TransformMatrix matrix) {
    for (auto figure : _figures) {
        figure.Transform(matrix);
    }
}



void QtSceneDrawer::DrawScene(Scene& scene) {
    QPainter painter(_widget);
    painter.setRenderHint(QPainter::Antialiasing);

    for (auto figure : scene.GetFigures()) {
        for (auto& edge : figure.GetEdges()) {
            painter.drawLine(
                QPointF(edge.GetBegin().GetPosition().x, edge.GetBegin().GetPosition().y),
                QPointF(edge.GetEnd().GetPosition().x, edge.GetEnd().GetPosition().x)
            );
        }
        figure.GetVertices();
    }
}
