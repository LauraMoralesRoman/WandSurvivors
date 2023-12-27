#pragma once

#include "result.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

namespace input_manager::inputSystem {
enum class ActionType { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, ATTACK };

class InputSystem {
public:
  void mapKeyToAction(SDL_KeyCode key, ActionType action);

  void mapMouseToAction(ActionType action);

  bool isActionMapped(ActionType action) const;

  using FunCheckMapErr = Result<ActionType, std::string>;
  FunCheckMapErr pressKey(SDL_KeyCode key);

private:
  std::unordered_map<SDL_KeyCode, ActionType> keyMappings;
  std::unordered_map<ActionType, bool> actions;
  bool isMouseLeftClicked = false;
};
} // namespace input_manager::inputSystem
