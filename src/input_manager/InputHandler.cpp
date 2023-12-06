#include "InputHandler.hpp"
#include <iostream>

void InputHandler::mapKeyToAction(SDL_KeyCode key, ActionType action) {
  auto it = InputHandler::keyMappings.find(key);

  if (it == InputHandler::keyMappings.end()) {
    InputHandler::keyMappings.emplace(key, action);
    InputHandler::actions.emplace(action, true);
    std::cout << "Mapeado correctamente" << std::endl;
  }
}

void InputHandler::mapMouseToAction(ActionType action) {

  actions[action] = false;
}

bool InputHandler::isActionTriggered(ActionType action) const {
  auto it = actions.find(action);

  if (it != actions.end()) {
    return it->second;
  }

  return false;
}
