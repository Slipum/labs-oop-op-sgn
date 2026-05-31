#include "scene.h"

#include <algorithm>
#include <limits>

void Scene::Transform(const TransformMatrix& matrix) {
    for (auto& figure : _figures) {
        figure.Transform(matrix);
    }
}

void Scene::AddObjectRotation(float x, float y, float z) {
    _objectRotation.x += x;
    _objectRotation.y += y;
    _objectRotation.z += z;
}

Point3D Scene::GetCenter() const {
    bool hasPoint = false;

    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float minZ = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float maxY = std::numeric_limits<float>::lowest();
    float maxZ = std::numeric_limits<float>::lowest();

    auto includePoint = [&](const Point3D& point) {
        hasPoint = true;

        minX = std::min(minX, point.x);
        minY = std::min(minY, point.y);
        minZ = std::min(minZ, point.z);
        maxX = std::max(maxX, point.x);
        maxY = std::max(maxY, point.y);
        maxZ = std::max(maxZ, point.z);
    };

    for (const auto& figure : _figures) {
        for (const auto& vertex : figure.GetVertices()) {
            includePoint(vertex.GetPosition());
        }

        if (figure.GetVertices().empty()) {
            for (const auto& edge : figure.GetEdges()) {
                if (edge.GetBegin()) {
                    includePoint(edge.GetBegin()->GetPosition());
                }

                if (edge.GetEnd()) {
                    includePoint(edge.GetEnd()->GetPosition());
                }
            }
        }
    }

    if (!hasPoint) {
        return {0.0f, 0.0f, 0.0f};
    }

    return {
        (minX + maxX) / 2.0f,
        (minY + maxY) / 2.0f,
        (minZ + maxZ) / 2.0f
    };
}
