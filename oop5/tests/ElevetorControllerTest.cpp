#include <gtest/gtest.h>
#include "abstructs/controller/controller.h"

TEST(ElevatorControllerTest, setGetFloor) {
    // auto v1 = std::make_shared<Vertex>(1, 0, 0);
    // auto v2 = std::make_shared<Vertex>(0, 1, 0);
    //
    // Edge e(v1, v2);
    //
    // auto m = TransformMatrixBuilder::CreateMoveMatrix(5, 0, 0);
    //
    // v1->Transform(m);
    // v2->Transform(m);
    //
    // EXPECT_FLOAT_EQ(e.GetBegin()->GetPosition().x, 6);
    // EXPECT_FLOAT_EQ(e.GetEnd()->GetPosition().x, 5);
    ElevatorController controller(1, 10);
    controller.setFloor(5);

    EXPECT_FLOAT_EQ(controller.getFloor(), 5);
    EXPECT_ANY_THROW(controller.setFloor(15));
}