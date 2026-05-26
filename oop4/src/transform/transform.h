#ifndef OOP4_TRANSFORM_H
#define OOP4_TRANSFORM_H
#include "../scene/object/point.h"

#define MATRIX_SIZE 4

class TransformMatrix {
public:
    TransformMatrix operator*(TransformMatrix m);
    Point3D TransformPoint(Point3D p);
private:
    float _matr[MATRIX_SIZE][MATRIX_SIZE];
};

class TransformMatrixBuilder {
public:
    static TransformMatrix CreateRotationMatrix(float x, float y, float z);
    static TransformMatrix CreateMoveMatrix(float x, float y, float z);
    static TransformMatrix CreateScaleMatrix(float x, float y, float z);
};

#endif //OOP4_TRANSFORM_H
