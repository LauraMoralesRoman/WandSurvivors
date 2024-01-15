#include "input_manager/InputSystem.hpp"

#include "../include/raylib.h"
#include "gtest/gtest.h"

TEST(InputSystemTest, MapKeyToActionTest) {
  auto &input = input_manager::inputSystem::InputSystem::getInstance();

  // key is mapped
  input.mapKeyToAction(KEY_A,
                       input_manager::inputSystem::ActionType::MOVE_RIGHT);

  EXPECT_EQ(
      input.isActionMapped(input_manager::inputSystem::ActionType::MOVE_RIGHT),
      true);
}

// expected behaviour
TEST(InputSystemTest, PressMappedKeyTest) {
  auto &input = input_manager::inputSystem::InputSystem::getInstance();

  input.mapKeyToAction(KEY_D,
                       input_manager::inputSystem::ActionType::MOVE_RIGHT);

  auto result = input.pressKey(KEY_D);

  EXPECT_TRUE(result.valid());
  EXPECT_EQ(result.value(), input_manager::inputSystem::ActionType::MOVE_RIGHT);
}

// intentional fail test
TEST(InputSystemTest, PressUnmappedKeyTest_Fail) {
  auto &input = input_manager::inputSystem::InputSystem::getInstance();

  auto result = input.pressKey(KEY_B);

  EXPECT_FALSE(result.valid());
  EXPECT_EQ(result.error(), "Key not mapped");
}
