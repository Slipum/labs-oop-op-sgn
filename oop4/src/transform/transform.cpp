#include "transform.h"

Point3D TransformMatrix::TransformPoint(Point3D p) {
    Point3D result;

    result.x =
        p.x * _matr[0][0] +
        p.y * _matr[0][1] +
        p.z * _matr[0][2] +
        _matr[0][3];

    result.y =
        p.x * _matr[1][0] +
        p.y * _matr[1][1] +
        p.z * _matr[1][2] +
        _matr[1][3];

    result.z =
        p.x * _matr[2][0] +
        p.y * _matr[2][1] +
        p.z * _matr[2][2] +
        _matr[2][3];

    return result;
}

TransformMatrix TransformMatrixBuilder::CreateMoveMatrix(float x, float y, float z) {  }

TransformMatrix TransformMatrixBuilder::CreateRotationMatrix(float x, float y, float z) {  }

TransformMatrix TransformMatrixBuilder::CreateScaleMatrix(float x, float y, float z) {  }
