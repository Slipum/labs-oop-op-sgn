#include <gtest/gtest.h>
#include "../src/scene/scene.h"
#include "../src/entities/abstructs/vertex.h"
#include "../src/entities/abstructs/figure.h"
#include "../src/math/transform.h"

TEST(SceneTest, CreateSceneWithFigures) {
    Figure f;
    f.AddVertex(Vertex(1, 2, 3));

    std::vector<Figure> figures;
    figures.push_back(f);

    Scene scene(std::move(figures));
    EXPECT_EQ(scene.GetFigures().size(), 1);
}

TEST(SceneTest, SceneOwnsFigures) {
    Scene scene({Figure()});

    EXPECT_NO_THROW({
        auto size = scene.GetFigures().size();
        EXPECT_GE(size, 0);
    });
}

TEST(SceneTest, TransformMovesAllFigures) {
    Figure f;

    f.AddVertex(Vertex(1, 0, 0));
    f.AddVertex(Vertex(0, 1, 0));

    Scene scene({f});

    auto m = TransformMatrixBuilder::CreateMoveMatrix(10, 0, 0);

    scene.Transform(m);

    const auto& fig = scene.GetFigures()[0];

    EXPECT_FLOAT_EQ(fig.GetVertices()[0].GetPosition().x, 11);
    EXPECT_FLOAT_EQ(fig.GetVertices()[1].GetPosition().x, 10);
}

TEST(SceneTest, EmptyScene) {
    Scene scene(std::vector<Figure>{});

    EXPECT_EQ(scene.GetFigures().size(), 0);

    auto m = TransformMatrixBuilder::CreateMoveMatrix(1, 1, 1);

    EXPECT_NO_THROW(scene.Transform(m));
}

TEST(SceneTest, CenterUsesBoundingBox) {
    Figure f;
    f.AddVertex(Vertex(0, 10, -2));
    f.AddVertex(Vertex(10, 20, 6));

    Scene scene({f});

    auto center = scene.GetCenter();

    EXPECT_FLOAT_EQ(center.x, 5);
    EXPECT_FLOAT_EQ(center.y, 15);
    EXPECT_FLOAT_EQ(center.z, 2);
}

TEST(SceneTest, MultipleFiguresTransform) {
    Figure f1;
    f1.AddVertex(Vertex(1, 0, 0));

    Figure f2;
    f2.AddVertex(Vertex(0, 1, 0));

    Scene scene({f1, f2});

    auto m = TransformMatrixBuilder::CreateMoveMatrix(5, 0, 0);

    scene.Transform(m);

    EXPECT_FLOAT_EQ(scene.GetFigures()[0].GetVertices()[0].GetPosition().x, 6);
    EXPECT_FLOAT_EQ(scene.GetFigures()[1].GetVertices()[0].GetPosition().x, 5);
}

TEST(SceneTest, SceneCopiesFiguresCorrectly) {
    Figure f;
    f.AddVertex(Vertex(1, 2, 3));

    std::vector<Figure> figs;
    figs.push_back(f);

    Scene scene(std::move(figs));

    Scene scene2 = scene;

    EXPECT_EQ(scene2.GetFigures().size(), 1);
}

TEST(SceneTest, ScenesAreIndependent) {
    Figure f;
    f.AddVertex(Vertex(1, 0, 0));

    Scene scene1({f});
    Scene scene2 = scene1;

    auto m = TransformMatrixBuilder::CreateMoveMatrix(10, 0, 0);

    scene1.Transform(m);

    EXPECT_FLOAT_EQ(scene1.GetFigures()[0].GetVertices()[0].GetPosition().x, 11);
    EXPECT_FLOAT_EQ(scene2.GetFigures()[0].GetVertices()[0].GetPosition().x, 1);
}
