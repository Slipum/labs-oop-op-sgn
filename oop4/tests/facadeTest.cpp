#include <gtest/gtest.h>
#include "../src/facade.h"

TEST(FacadeTest, LoadSceneWorks) {
    FakeFileReader reader;
    FakeDrawer drawer;
    Scene scene;

    Facade facade(reader, drawer, scene);

    auto result = facade.LoadScene("any.csv", {});

    EXPECT_TRUE(result.IsSuccess());
    EXPECT_EQ(scene.GetFigures().size(), 1);
}

TEST(FacadeTest, ScaleSceneKeepsSceneCenter) {
    FakeFileReader reader;
    FakeDrawer drawer;
    Figure f;
    f.AddVertex(Vertex(10, 0, 0));
    f.AddVertex(Vertex(12, 0, 0));
    Scene scene({f});

    Facade facade(reader, drawer, scene);

    auto result = facade.ScaleScene(2, 2, 2);

    EXPECT_TRUE(result.IsSuccess());
    EXPECT_FLOAT_EQ(scene.GetCenter().x, 11);
}

TEST(FacadeTest, MoveSceneLocalUsesObjectRotation) {
    FakeFileReader reader;
    FakeDrawer drawer;
    Figure f;
    f.AddVertex(Vertex(0, 0, 0));
    Scene scene({f});
    Facade facade(reader, drawer, scene);

    facade.RotateScene(0, -M_PI / 2, 0);
    auto result = facade.MoveSceneLocal(0, 0, 1);

    EXPECT_TRUE(result.IsSuccess());
    EXPECT_NEAR(scene.GetCenter().x, -1, 0.001);
    EXPECT_NEAR(scene.GetCenter().z, 0, 0.001);
}
