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
    TransformMatrix rx;
    TransformMatrix ry;
    TransformMatrix rz;

    float cx = cos(x), sx = sin(x);
    float cy = cos(y), sy = sin(y);
    float cz = cos(z), sz = sin(z);

    rx._matr[1][1] = cx;
    rx._matr[1][2] = -sx;
    rx._matr[2][1] = sx;
    rx._matr[2][2] = cx;

    ry._matr[0][0] = cy;
    ry._matr[0][2] = sy;
    ry._matr[2][0] = -sy;
    ry._matr[2][2] = cy;

    rz._matr[0][0] = cz;
    rz._matr[0][1] = -sz;
    rz._matr[1][0] = sz;
    rz._matr[1][1] = cz;

    return rz * ry * rx;
}