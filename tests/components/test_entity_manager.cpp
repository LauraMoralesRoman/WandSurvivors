#include "components/entity.hpp"
#include "components/manager.hpp"
#include "components/module.hpp"
#include "components/test_component.hpp"
#include "defs.hpp"
#include "resources.hpp"
#include <gtest/gtest.h>
#include <memory>

class ComponentsTest : public ::testing::Test {
	protected:
		std::unique_ptr<core::components::Module<GameObject>> mod;

		void SetUp() override {
			const auto path = resource_path("build/components/libbasic_module.so");
			self->mod = std::make_unique<core::components::Module<GameObject>>(core::components::load_module<GameObject>(path).value());
		}
};

TEST_F(ComponentsTest, InstantiateEntity) {
	core::components::EntityManager<GameObject> manager(*self->mod);

	auto& instance = manager.create_instance();
	auto& another_instance = instance;

	ASSERT_EQ(instance->foo(1, 2), 3);
	ASSERT_EQ(another_instance->foo(1, 2), 3);
}

TEST_F(ComponentsTest, RemoveEntity) {
	core::components::EntityManager<GameObject> manager(*self->mod);

	auto& instance = manager.create_instance();
	instance.remove();

	// Should be marked and not deleted
	ASSERT_EQ(manager.size(), 1);
	auto num_deleted = manager.remove_marked();
	ASSERT_EQ(manager.size(), 0);
	ASSERT_EQ(num_deleted, 1);
}

TEST_F(ComponentsTest, RemoveMultipleEntities) {
	core::components::EntityManager<GameObject> manager(*self->mod);

	constexpr auto to_create = 100;
	for (auto i = 0; i < to_create; i++) {
		auto& instance = manager.create_instance();
		if (i < (to_create / 2)) {
			instance.remove();
		}
	}

	ASSERT_EQ(manager.size(), to_create);
	auto num_deleted = manager.remove_marked();
	ASSERT_EQ(manager.size(), to_create / 2);
	ASSERT_EQ(num_deleted, to_create / 2);
}
