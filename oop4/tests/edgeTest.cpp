#include <gtest/gtest.h>
#include "../src/entities/abstructs/edge.h"

TEST(EdgeTest, CreateEdge) {
    auto v1 = std::make_shared<Vertex>(0, 0, 0);
    auto v2 = std::make_shared<Vertex>(1, 1, 1);

    Edge e(v1, v2);

    EXPECT_EQ(e.GetBegin(), v1);
    EXPECT_EQ(e.GetEnd(), v2);
}

TEST(EdgeTest, EdgeRemainsValidAfterVertexTransform) {
    auto v1 = std::make_shared<Vertex>(1, 0, 0);
    auto v2 = std::make_shared<Vertex>(0, 1, 0);

    Edge e(v1, v2);

    auto m = TransformMatrixBuilder::CreateMoveMatrix(5, 0, 0);

    v1->Transform(m);
    v2->Transform(m);

    EXPECT_FLOAT_EQ(e.GetBegin()->GetPosition().x, 6);
    EXPECT_FLOAT_EQ(e.GetEnd()->GetPosition().x, 5);
}