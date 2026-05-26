#include <gtest/gtest.h>
#include "../src/entities/abstructs/figure.h"
#include "../src/entities/abstructs/vertex.h"
#include "../src/math/transform.h"

TEST(FigureTest, EmptyFigure) {
    Figure f;

    EXPECT_EQ(f.GetVertices().size(), 0);
    EXPECT_EQ(f.GetEdges().size(), 0);
}

TEST(FigureTest, TransformEmptyFigure) {
    Figure f;

    auto m = TransformMatrixBuilder::CreateMoveMatrix(10, 10, 10);

    EXPECT_NO_THROW(f.Transform(m));
}

TEST(FigureTest, TransformKeepsVertexCount) {
    Figure f;

    f.AddVertex(Vertex(1, 2, 3));
    f.AddVertex(Vertex(4, 5, 6));

    auto m = TransformMatrixBuilder::CreateScaleMatrix(2, 2, 2);

    f.Transform(m);

    EXPECT_EQ(f.GetVertices().size(), 2);
}

TEST(FigureTest, TransformMovesAllVertices) {
    Figure f;

    f.AddVertex(Vertex(1, 0, 0));
    f.AddVertex(Vertex(0, 1, 0));

    auto m = TransformMatrixBuilder::CreateMoveMatrix(10, 0, 0);

    f.Transform(m);

    EXPECT_FLOAT_EQ(f.GetVertices()[0].GetPosition().x, 11);
    EXPECT_FLOAT_EQ(f.GetVertices()[1].GetPosition().x, 10);
}