#ifndef OOP4_VERTEX_H
#define OOP4_VERTEX_H
#include "../object.h"
#include "../point.h"
#include <memory>

class Vertex : public SceneObject {
public:
    Vertex(float x, float y, float z) : _position{x, y, z} {}

    const Point3D& GetPosition() const { return _position; };

    void Transform(const TransformMatrix& matrix) override
        { _position = matrix.TransformPoint(_position); };
private:
    Point3D _position;
};

#endif //OOP4_VERTEX_H
