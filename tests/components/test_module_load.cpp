#include "components/components.hpp"
#include <format>
#include <gtest/gtest.h>
#include <resources.hpp>
#include "utils.hpp"

#include <string>

#include <components/test_component.hpp>
#include <core.hpp>
#include <variant>

TEST(Components, LoadModule) {
	const auto path = resource_path("build/components/libbasic_module.so");

	auto mod = core::components::load_module<GameObject>(path);

	if (!mod.valid()) {
		std::string error = std::format("Loaded module should be of the Ok variant\n{}", repr_mod_load_error(mod.error()));
		FAIL() << error;
	}
	auto res = mod.value();

	auto instance = res.instantiate();
	ASSERT_NE(instance, nullptr) << "Loaded instance function is null";

	ASSERT_EQ(instance->foo(1, 2), 3) << "The sum method does not work properly, something failed when instantiating";
}

TEST(Components, LoadModuleNoFunction) {
	const auto path = resource_path("build/components/libno_instance_mod.so");

	auto mod = core::components::load_module<GameObject>(path);

	ASSERT_FALSE(mod.valid()) << "Module shouldn't have loaded because it didn't have an instantiate funciton";
	
	auto err = mod.error();
	ASSERT_TRUE(std::holds_alternative<core::components::LackingMethodError>(err));
}

TEST(Components, LoadModuleInvalidFile) {
	auto mod = core::components::load_module<GameObject>("__invalid_path");

	ASSERT_FALSE(mod.valid());

	auto err = mod.error();
	ASSERT_TRUE(std::holds_alternative<core::components::InvalidFileError>(err));
}
