#include "components/module.hpp"
#include "components/system.hpp"
#include "components/test_component.hpp"
#include "resources.hpp"
#include "utils/metafunctions.hpp"
#include "utils/type_map.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>

class EntityManagerTest : public ::testing::Test {
	protected:
		std::unique_ptr<core::components::Module<GameObject>> mod;

		void SetUp() override {
			const auto path = resource_path("build/components/libbasic_module.so");
			self->mod = std::make_unique<core::components::Module<GameObject>>(core::components::load_module<GameObject>(path).value());
		}
};

decltype(auto) mapping() {
	core::utils::TypeMap<std::string> map;
	map.set<GameObject>(resource_path("build/components/libbasic_module.so"));
	return map;
}

using GameEntities = core::metafunc::TypeList<
	GameObject
>;

TEST_F(EntityManagerTest, EntityManager) {
	auto map = mapping();
	core::components::GameEntityManager<GameEntities> manager(map);

	// TODO: should continue the game
	auto instance = manager.instantiate<GameObject>();

	ASSERT_NE(instance, nullptr);
	ASSERT_EQ(instance->get()->foo(1, 2), 3);
}
