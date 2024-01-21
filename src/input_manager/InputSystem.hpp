#pragma once

#include "raylib.h"
#include "result.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace input_manager::inputSystem {
enum class ActionType {
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,
  ATTACK,
  INTERACT,
  QUIT
};

class InputSystem {
public:
  static InputSystem &getInstance();

  InputSystem(const InputSystem &) = delete;
  void operator=(const InputSystem &) = delete;

  void mapKeyToAction(int key, ActionType action);

  bool isActionMapped(ActionType action) const;

  const std::vector<KeyboardKey> getMappedKeys() const;

  using FunCheckMapErr = Result<ActionType, std::string>;
  FunCheckMapErr pressKey(int key);

private:
  InputSystem() {}

  ~InputSystem() {}
  std::unordered_map<int, ActionType> keyMappings;
  std::unordered_map<ActionType, bool> actions;
};
} // namespace input_manager::inputSystem
