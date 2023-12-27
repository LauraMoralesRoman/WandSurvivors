#include "input_manager/InputSystem.hpp"
#include "gtest/gtest.h"

TEST(InputSystemTest, MapKeyToActionTest) {
  input_manager::inputSystem::InputSystem input;

  // key is mapped
  input.mapKeyToAction(SDLK_a,
                       input_manager::inputSystem::ActionType::MOVE_RIGHT);

  EXPECT_EQ(
      input.isActionMapped(input_manager::inputSystem::ActionType::MOVE_RIGHT),
      true);
}

// expected behaviour
TEST(InputSystemTest, PressMappedKeyTest) {
  input_manager::inputSystem::InputSystem input;

  input.mapKeyToAction(SDLK_d,
                       input_manager::inputSystem::ActionType::MOVE_RIGHT);

  auto result = input.pressKey(SDLK_d);

  EXPECT_TRUE(result.valid());
  EXPECT_EQ(result.value(), input_manager::inputSystem::ActionType::MOVE_RIGHT);
}

// intentional fail test
TEST(InputSystemTest, PressUnmappedKeyTest_Fail) {
  input_manager::inputSystem::InputSystem input;

  auto result = input.pressKey(SDLK_b);

  EXPECT_FALSE(result.valid());
  EXPECT_EQ(result.error(), "Key not mapped");
}
