#include "resource_manager/resource_manager.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <vector>

TEST(resources, resource_locator) {
	auto path = core::resources::get_resource_location_base("this", {
		"is",
		"a",
		"path"
	});

	std::vector<std::string> stringed;
	std::copy(path.begin(), path.end(), std::back_inserter(stringed));
	std::vector<std::string> expected {
		"is",
	  	"a",
	  	"path"
	};

	std::cout << "Generated path: " << std::endl;

	for (const auto& [lhs, rhs] : std::views::zip(stringed, expected)) {
		ASSERT_EQ(lhs, rhs) << "All elements should be equal and in order";
	}
}
