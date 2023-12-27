#include "components/module.hpp"
#include "components/system.hpp"
#include "components/test_component.hpp"
#include "resources.hpp"
#include <gtest/gtest.h>
#include <memory>

class EntityManagerTest : public ::testing::Test {
	protected:
		std::unique_ptr<core::components::Module<GameObject>> mod;

		void SetUp() override {
			const auto path = resource_path("build/components/libbasic_module.so");
			self->mod = std::make_unique<core::components::Module<GameObject>>(core::components::load_module<GameObject>(path).value());
		}
};

TEST_F(EntityManagerTest, EntityManager) {
	core::components::GameEntityManager manager;

	// TODO: should continue the game
}
