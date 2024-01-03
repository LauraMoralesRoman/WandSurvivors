#pragma once
#include "../input_manager/InputSystem.hpp"
#include "../input_manager/PubSubSystem.hpp"

using namespace input_manager::pubSub;
using namespace input_manager::inputSystem;

class PlayerInputHandler {
public:
  virtual void subscribe(ActionType actiontype,
                         PubSubSystem::Callback callback) = 0;

  virtual void mute(PubSubSystem::Topic topic) = 0;

  virtual ~PlayerInputHandler() {}

private:
};
