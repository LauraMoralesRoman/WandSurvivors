#include "InputSystem.hpp"

namespace input_manager::inputSystem {

InputSystem &InputSystem::getInstance() {
  static InputSystem instance;
  return instance;
}

void InputSystem::mapKeyToAction(int key, ActionType action) {
  auto it = keyMappings.find(key);

  if (it == keyMappings.end()) {
    keyMappings.emplace(key, action);
    actions.emplace(action, true);
  }
}

void InputSystem::mapMouseToAction(ActionType action) {
  actions[action] = false;
}

bool InputSystem::isActionMapped(ActionType action) const {
  auto it = actions.find(action);

  if (it != actions.end()) {
    return it->second;
  }

  return false;
}

InputSystem::FunCheckMapErr InputSystem::pressKey(int key) {
  auto it = keyMappings.find(key);

  if (it != keyMappings.end()) {
    return FunCheckMapErr(it->second);
  }

  else {
    return FunCheckMapErr("Key not mapped");
  }
}
} // namespace input_manager::inputSystem
