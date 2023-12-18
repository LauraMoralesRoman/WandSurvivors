#include "../src/input_manager/InputHandler.hpp"
#include "gtest/gtest.h"

TEST(InputHandlerTest, MapKeyToActionTest) {
  InputHandler inputHandler;

  // key is mapped
  inputHandler.mapKeyToAction(SDLK_a, ActionType::MOVE_RIGHT);

  EXPECT_EQ(inputHandler.isActionTriggered(ActionType::MOVE_RIGHT), true);
}
