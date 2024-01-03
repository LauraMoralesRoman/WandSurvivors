#pragma once
#include "InputSystem.hpp"
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace input_manager::pubSub {
class PubSubSystem {
public:
  static PubSubSystem &getInstance();

  PubSubSystem(const PubSubSystem &) = delete;
  void operator=(const PubSubSystem &) = delete;

  using Callback = std::function<void()>;
  using Topic = std::vector<Callback>;

  bool exists(inputSystem::ActionType);

  using FunGetTopicErr = Result<Topic, std::string>;
  FunGetTopicErr getTopic(inputSystem::ActionType);

  void subscribe(inputSystem::ActionType, Callback);

  void publish(inputSystem::ActionType);

private:
  PubSubSystem() {}

  ~PubSubSystem() {}

  std::unordered_map<inputSystem::ActionType, Topic> topics;
};
} // namespace input_manager::pubSub
