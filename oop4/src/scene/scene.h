#ifndef OOP4_SCENE_H
#define OOP4_SCENE_H
#include <vector>
#include "entities/abstructs/figure.h"
#include "scene/camera.h"

class Scene {
public:
    Scene() = default;
    Scene(std::vector<Figure> figures)
    : _figures(std::move(figures)) {}

    const std::vector<Figure>& GetFigures() const { return _figures;};
    const Camera& GetCamera() const { return _camera; }
    Camera& GetCamera() { return _camera; }

    void Transform(const TransformMatrix& matrix);
    Point3D GetCenter() const;
    const Point3D& GetObjectRotation() const { return _objectRotation; }
    void AddObjectRotation(float x, float y, float z);
private:
    std::vector<Figure> _figures;
    Camera _camera;
    Point3D _objectRotation{0.0f, 0.0f, 0.0f};
};

#endif //OOP4_SCENE_H
