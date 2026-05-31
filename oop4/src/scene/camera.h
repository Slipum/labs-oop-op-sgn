#ifndef OOP4_CAMERA_H
#define OOP4_CAMERA_H

#include "entities/point.h"
#include "math/transform.h"

class Camera {
public:
    Camera();

    const Point3D& GetPosition() const { return _position; }
    const Point3D& GetRotation() const { return _rotation; }

    TransformMatrix GetViewMatrix() const;

private:
    Point3D _position;
    Point3D _rotation;
};

#endif //OOP4_CAMERA_H
