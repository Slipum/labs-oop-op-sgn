#include <gtest/gtest.h>

#include "abstructs/builder/builder.h"

TEST(ElevatorControllerTests, ElevatorControllerTest) {
    auto elevator = ElevatorBuilder().build();
    EXPECT_EQ(elevator->controller().targetFloor(), 1);
    elevator->controller().setTargetFloor(10);
    EXPECT_EQ(elevator->controller().targetFloor(), 10);
}

// ElevatorTimerHost immediateTimerHost(ElevatorManager &manager) {
//     return ElevatorTimerHost{
//         [&manager](int) { manager.onMove(); },
//         []() {},
//         [&manager](int) { manager.onWait(); },
//         [&manager](int) { manager.onDoorOpen(); },
//         [&manager](int) { manager.onDoorClose(); },
//     };
// }
//
// TEST(ElevatorManagerTest, StartsOnFirstFloor) {
//     auto manager = ElevatorBuilder().build();
//     EXPECT_EQ(manager->elevator().controller().currentFloor(), ElevatorConfig::MIN_FLOOR);
//     EXPECT_TRUE(manager->elevator().controller().pendingFloors().empty());
// }
//
// TEST(ElevatorManagerTest, AcceptsValidCabinRequest) {
//     auto manager = ElevatorBuilder().withDefaults().buildManager();
//     manager->callFromCabin(3);
//     EXPECT_TRUE(manager->elevator().controller().hasPendingFloor(3));
// }
//
// TEST(ElevatorManagerTest, RejectsInvalidFloorRequest) {
//     auto manager = ElevatorBuilder().withDefaults().buildManager();
//     manager->callFromFloor(0);
//     manager->callFromFloor(ElevatorConfig::FLOOR_COUNT + 1);
//     EXPECT_TRUE(manager->elevator().controller().pendingFloors().empty());
// }
//
// TEST(ElevatorManagerTest, MovesToRequestedFloor) {
//     auto manager = ElevatorBuilder().withDefaults().buildManager();
//     manager->setTimerHost(immediateTimerHost(*manager));
//     manager->callFromCabin(3);
//
//     const auto &ctrl = manager->elevator().controller();
//     EXPECT_EQ(ctrl.currentFloor(), 3);
//     EXPECT_EQ(ctrl.state(), ControllerState::Free);
//     EXPECT_TRUE(ctrl.pendingFloors().empty());
// }
//
// TEST(ElevatorManagerTest, KeepsMovingWhenNewRequestDuringTrip) {
//     auto manager = ElevatorBuilder().buildManager();
//     manager->setTimerHost(immediateTimerHost(*manager));
//
//     manager->callFromCabin(3);
//     EXPECT_EQ(manager->elevator().controller().currentFloor(), 3);
//
//     manager->callFromCabin(5);
//     const auto &ctrl = manager->elevator().controller();
//     EXPECT_EQ(ctrl.currentFloor(), 5);
//     EXPECT_EQ(ctrl.state(), ControllerState::Free);
// }
