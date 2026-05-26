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