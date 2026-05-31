#ifndef OOP4_TRANSFORM_H
#define OOP4_TRANSFORM_H

#define SIZE_MATRIX 4
#include "../entities/point.h"

class TransformMatrix {
public:
    TransformMatrix();

    TransformMatrix operator*(const TransformMatrix& matrix) const;
    Point3D TransformPoint(const Point3D& point) const;
private:
    float _matr[SIZE_MATRIX][SIZE_MATRIX];
    friend class TransformMatrixBuilder;
};

class TransformMatrixBuilder {
public:
    static TransformMatrix CreateRotationXMatrix(float angle);
    static TransformMatrix CreateRotationYMatrix(float angle);
    static TransformMatrix CreateRotationZMatrix(float angle);

    static TransformMatrix CreateRotationMatrix(float x, float y, float z);
    static TransformMatrix CreateMoveMatrix(float x, float y, float z);
    static TransformMatrix CreateScaleMatrix(float x, float y, float z);
};

#endif //OOP4_TRANSFORM_H
