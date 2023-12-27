#pragma once
#include "InputSystem.hpp"
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace input_manager::pubSub {
class PubSubSystem {
public:
  using Callback = std::function<void()>;
  using Topic = std::vector<Callback>;

  bool exists(inputSystem::ActionType);

  using FunGetTopicErr = Result<Topic, std::string>;
  FunGetTopicErr getTopic(inputSystem::ActionType);

  void subscribe(inputSystem::ActionType, Callback);

  void publish(inputSystem::ActionType);

private:
  std::unordered_map<inputSystem::ActionType, Topic> topics;
};
} // namespace input_manager::pubSub
