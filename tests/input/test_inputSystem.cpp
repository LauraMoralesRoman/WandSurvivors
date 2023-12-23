#include "input_manager/InputSystem.hpp"
#include "gtest/gtest.h"

TEST(InputSystemTest, MapKeyToActionTest) {
  InputSystem inputSystem;

  // key is mapped
  inputSystem.mapKeyToAction(SDLK_a, ActionType::MOVE_RIGHT);

  EXPECT_EQ(inputSystem.isActionMapped(ActionType::MOVE_RIGHT), true);
}

// expected behaviour
TEST(InputSystemTest, PressMappedKeyTest) {
  InputSystem inputSystem;

  inputSystem.mapKeyToAction(SDLK_d, ActionType::MOVE_RIGHT);

  auto result = inputSystem.pressKey(SDLK_d);

  EXPECT_TRUE(result.valid());
  EXPECT_EQ(result.value(), ActionType::MOVE_RIGHT);
}

// intentional fail test
TEST(InputSystemTest, PressUnmappedKeyTest_Fail) {
  InputSystem inputSystem;

  auto result = inputSystem.pressKey(SDLK_b);

  EXPECT_FALSE(result.valid());
  EXPECT_EQ(result.error(), "Key not mapped");
}
