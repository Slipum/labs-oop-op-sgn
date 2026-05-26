#include <gtest/gtest.h>
#include "../src/entities/abstructs/vertex.h"
#include "../src/math/transform.h"

TEST(VertexTest, CreateVertex) {
    Vertex v(1, 2, 3);

    EXPECT_FLOAT_EQ(v.GetPosition().x, 1);
    EXPECT_FLOAT_EQ(v.GetPosition().y, 2);
    EXPECT_FLOAT_EQ(v.GetPosition().z, 3);
}

TEST(VertexTest, MoveTransform) {
    Vertex v(1, 2, 3);

    auto m = TransformMatrixBuilder::CreateMoveMatrix(10, 0, 0);
    v.Transform(m);

    EXPECT_FLOAT_EQ(v.GetPosition().x, 11);
    EXPECT_FLOAT_EQ(v.GetPosition().y, 2);
    EXPECT_FLOAT_EQ(v.GetPosition().z, 3);
}

TEST(VertexTest, ScaleTransform) {
    Vertex v(1, 2, 3);

    auto m = TransformMatrixBuilder::CreateScaleMatrix(2, 3, 4);
    v.Transform(m);

    EXPECT_FLOAT_EQ(v.GetPosition().x, 2);
    EXPECT_FLOAT_EQ(v.GetPosition().y, 6);
    EXPECT_FLOAT_EQ(v.GetPosition().z, 12);
}

TEST(VertexTest, RotateZ90Degrees) {
    Vertex v(1, 0, 0);

    auto m = TransformMatrixBuilder::CreateRotationMatrix(0, 0, M_PI / 2);
    v.Transform(m);

    EXPECT_NEAR(v.GetPosition().x, 0, 0.001);
    EXPECT_NEAR(v.GetPosition().y, 1, 0.001);
}

