#include "transform.h"

#include <cmath>

TransformMatrix::TransformMatrix() {
    for (int i = 0; i < SIZE_MATRIX; i++) {
        for (int j = 0; j < SIZE_MATRIX; j++) {
            _matr[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

TransformMatrix TransformMatrix::operator*(
    const TransformMatrix& matrix
) const {
    TransformMatrix result;

    for (int i = 0; i < SIZE_MATRIX; i++) {
        for (int j = 0; j < SIZE_MATRIX; j++) {

            result._matr[i][j] = 0;

            for (int k = 0; k < SIZE_MATRIX; k++) {
                result._matr[i][j] +=
                    _matr[i][k] * matrix._matr[k][j];
            }
        }
    }

    return result;
}

Point3D TransformMatrix::TransformPoint(const Point3D& point) const {
    Point3D result;

    result.x =
        point.x * _matr[0][0] +
        point.y * _matr[0][1] +
        point.z * _matr[0][2] +
        _matr[0][3];

    result.y =
        point.x * _matr[1][0] +
        point.y * _matr[1][1] +
        point.z * _matr[1][2] +
        _matr[1][3];

    result.z =
        point.x * _matr[2][0] +
        point.y * _matr[2][1] +
        point.z * _matr[2][2] +
        _matr[2][3];

    return result;
}


TransformMatrix TransformMatrixBuilder::CreateMoveMatrix(
    float x, float y, float z
) {
    TransformMatrix m;

    m._matr[0][3] = x;
    m._matr[1][3] = y;
    m._matr[2][3] = z;

    return m;
}

TransformMatrix TransformMatrixBuilder::CreateScaleMatrix(
    float x, float y, float z
) {
    TransformMatrix m;

    m._matr[0][0] = x;
    m._matr[1][1] = y;
    m._matr[2][2] = z;

    return m;
}

TransformMatrix TransformMatrixBuilder::CreateRotationMatrix(
    float x, float y, float z
) {
    return CreateRotationZMatrix(z)
        * CreateRotationYMatrix(y)
        * CreateRotationXMatrix(x);
}

TransformMatrix TransformMatrixBuilder::CreateRotationXMatrix(float angle) {
    TransformMatrix rx;

    float c = cos(angle), s = sin(angle);

    rx._matr[1][1] = c;
    rx._matr[1][2] = -s;
    rx._matr[2][1] = s;
    rx._matr[2][2] = c;

    return rx;
}

TransformMatrix TransformMatrixBuilder::CreateRotationYMatrix(float angle) {
    TransformMatrix ry;

    float c = cos(angle), s = sin(angle);

    ry._matr[0][0] = c;
    ry._matr[0][2] = s;
    ry._matr[2][0] = -s;
    ry._matr[2][2] = c;

    return ry;
}

TransformMatrix TransformMatrixBuilder::CreateRotationZMatrix(float angle) {
    TransformMatrix rz;

    float c = cos(angle), s = sin(angle);

    rz._matr[0][0] = c;
    rz._matr[0][1] = -s;
    rz._matr[1][0] = s;
    rz._matr[1][1] = c;

    return rz;
}
