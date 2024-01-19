#include "InputSystem.hpp"
#include "raylib.h"
#include <algorithm>
#include <iterator>
#include <ranges>
#include <vector>

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
    return ActionType{it->second};
  }

  else {
    return FunCheckMapErr("Key not mapped");
  }
}
} // namespace input_manager::inputSystem
//
const std::vector<KeyboardKey> input_manager::inputSystem::InputSystem::getMappedKeys() const {
	std::vector<KeyboardKey> output;
	auto keys = this->keyMappings 
		| std::ranges::views::keys
		| std::ranges::views::transform([](const auto& elem) { return static_cast<KeyboardKey>(elem); });

	std::copy(keys.begin(), keys.end(), std::back_inserter(output));
	return output;
}
