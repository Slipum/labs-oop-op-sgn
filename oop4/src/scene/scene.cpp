#include "scene.h"

void Scene::Transform(const TransformMatrix& matrix) {
    for (auto& figure : _figures) {
        figure.Transform(matrix);
    }
}