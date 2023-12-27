#include "input_manager/PubSubSystem.hpp"
#include "gtest/gtest.h"
#include <functional>
#include <sstream>
#include <streambuf>

TEST(PubSubSystemTest, SubscribeTest) {
  input_manager::pubSub::PubSubSystem system;
  auto action = input_manager::inputSystem::ActionType::MOVE_UP;
  std::function<void()> moveUpFunction = []() {
    std::cout << "Me muevo hacia arriba" << std::endl;
  };

  system.subscribe(action, moveUpFunction);

  auto topicResult = system.getTopic(action);
  ASSERT_TRUE(topicResult.valid()) << "Topic not found or created";

  auto topic = topicResult.value();
  ASSERT_GT(topic.size(), 0) << "No functions found in the topic";

  bool found = false;
  for (const auto &callback : topic) {
    if (typeid(callback) == typeid(moveUpFunction)) {
      found = true;
      break;
    }
  }

  EXPECT_TRUE(found) << "Subscribed function not found in the topic";
}

TEST(PubSubSystemTest, PublishTest) {
  input_manager::pubSub::PubSubSystem system;
  auto action = input_manager::inputSystem::ActionType::MOVE_UP;
  std::function<void()> moveUpFunction = []() {
    std::cout << "Me muevo hacia arriba" << std::endl;
  };

  system.subscribe(action, moveUpFunction);

  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  system.publish(action);
  std::cout.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_NE(output.find("Me muevo hacia arriba"), std::string::npos)
      << "MoveUpFunction was not called";
}
