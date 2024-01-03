#pragma once

#include "result.hpp"
#include <string>
#include <unordered_map>

namespace input_manager::inputSystem {
enum class ActionType { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, ATTACK };

class InputSystem {
public:
  static InputSystem &getInstance();

  InputSystem(const InputSystem &) = delete;
  void operator=(const InputSystem &) = delete;

  void mapKeyToAction(int key, ActionType action);

  void mapMouseToAction(ActionType action);

  bool isActionMapped(ActionType action) const;

  using FunCheckMapErr = Result<ActionType, std::string>;
  FunCheckMapErr pressKey(int key);

private:
  InputSystem() {}

  ~InputSystem() {}
  std::unordered_map<int, ActionType> keyMappings;
  std::unordered_map<ActionType, bool> actions;
  bool isMouseLeftClicked = false;
};
} // namespace input_manager::inputSystem
