#include "camera.h"

Camera::Camera()
    : _position{0.0f, 20.0f, -40.0f},
      _rotation{0.25f, 0.0f, 0.0f}
{
}


TransformMatrix Camera::GetViewMatrix() const {
    auto translate = TransformMatrixBuilder::CreateMoveMatrix(
        -_position.x,
        -_position.y,
        -_position.z
    );

    auto inverseRotation =
        TransformMatrixBuilder::CreateRotationXMatrix(-_rotation.x)
        * TransformMatrixBuilder::CreateRotationYMatrix(-_rotation.y)
        * TransformMatrixBuilder::CreateRotationZMatrix(-_rotation.z);

    return inverseRotation * translate;
}
