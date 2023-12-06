#include <algorithm>
#include <format>
#include <gtest/gtest.h>

#include "components/module.hpp"
#include "components/test_component.hpp"
#include "resources.hpp"
#include "utils.hpp"

#include <components/components.hpp>
#include <memory>
#include <vector>

TEST(Components, ReloadModule) {
	auto path_v1 = resource_path("build/components/libbasic_reload_v1.so");
	auto path_v2 = resource_path("build/components/libbasic_reload_v2.so");

	auto load_res = core::components::load_module<GameObject>(path_v1);
	auto mod = load_res.value();

	mod.path = path_v2; // This is a bit of a hack but wouldn't be necessary in a real scenario

	auto reload_res = core::components::reload_module(mod);
	if (!reload_res.valid()) {
		auto err_variant = reload_res.error();
		auto error = std::format("ReloadResult should be of the Ok variant: \n\t{}", repr_mod_load_error(err_variant.err));
		FAIL() << error;
	}

	auto reload = reload_res.value();
}

TEST(Components, ReplaceVTables) {
	auto path_v1 = resource_path("build/components/libbasic_reload_v1.so");
	auto path_v2 = resource_path("build/components/libbasic_reload_v2.so");

	auto mod = core::components::load_module<GameObject>(path_v1).value();
	mod.path = path_v2; // This is a bit of a hack but wouldn't be necessary in a real scenario
	auto reloaded_mod = core::components::reload_module(mod).value();

	auto instance = mod.instantiate();
	ASSERT_NE(instance, nullptr);
	
	std::vector<std::unique_ptr<GameObject>> v;
	v.push_back(std::move(instance));

	ASSERT_EQ(v[0]->foo(3, 2), 5); // v1 is addition
	core::components::set_vtables(reloaded_mod, v);
	ASSERT_EQ(v[0]->foo(3, 2), 6); // v2 is multiplication
}

TEST(Components, InvalidReload) {
	auto path_v1 = resource_path("build/components/libbasic_reload_v1.so");

	auto mod = core::components::load_module<GameObject>(path_v1).value();
	auto instance = mod.instantiate();
	std::vector<std::unique_ptr<GameObject>> v;
	v.push_back(std::move(instance));

	mod.path = "__invalid_mod"; // A bit of a hack
	auto reload_res = core::components::reload_module(mod);
	ASSERT_FALSE(reload_res.valid());
	
	auto reloaded = reload_res.error().prev_module;
	
	ASSERT_EQ(v[0]->foo(3, 2), 5) << "Should have default behavior";
	core::components::set_vtables(reloaded, v);
	ASSERT_EQ(v[0]->foo(3, 2), 5) << "Should have the same behavior because the new module couldn't be loaded";
}
