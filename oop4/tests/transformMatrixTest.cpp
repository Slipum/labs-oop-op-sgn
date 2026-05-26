#include <gtest/gtest.h>
#include "../src/math/transform.h"
#include "../src/entities/point.h"

TEST(MatrixTest, IdentityTransform) {
    TransformMatrix m;

    Point3D p{1, 2, 3};
    auto r = m.TransformPoint(p);

    EXPECT_FLOAT_EQ(r.x, 1);
    EXPECT_FLOAT_EQ(r.y, 2);
    EXPECT_FLOAT_EQ(r.z, 3);
}

TEST(MatrixTest, MoveTransform) {
    auto m = TransformMatrixBuilder::CreateMoveMatrix(10, 0, 0);

    Point3D p{1, 2, 3};
    auto r = m.TransformPoint(p);

    EXPECT_FLOAT_EQ(r.x, 11);
    EXPECT_FLOAT_EQ(r.y, 2);
    EXPECT_FLOAT_EQ(r.z, 3);
}

TEST(MatrixTest, ScaleTransform) {
    auto m = TransformMatrixBuilder::CreateScaleMatrix(2, 3, 4);

    Point3D p{1, 2, 3};
    auto r = m.TransformPoint(p);

    EXPECT_FLOAT_EQ(r.x, 2);
    EXPECT_FLOAT_EQ(r.y, 6);
    EXPECT_FLOAT_EQ(r.z, 12);
}

TEST(MatrixTest, RotationPreservesLength) {
    auto m = TransformMatrixBuilder::CreateRotationMatrix(0, 0, M_PI / 2);

    Point3D p{3, 4, 0};
    auto r = m.TransformPoint(p);

    float len = sqrt(r.x*r.x + r.y*r.y + r.z*r.z);

    EXPECT_NEAR(len, 5.0, 0.001);
}