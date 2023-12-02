#pragma once

#include <filesystem>
#include <string>

#ifndef TEST_RESOURCES_DIR
	#warning TEST_RESOURCES_DIR was not defined default folder will be used
	#define TEST_RESOURCES_DIR "./resources"
#endif

std::string resource_path(const std::string& name) {
	auto path = std::filesystem::path(TEST_RESOURCES_DIR);
	path.append(name);
	return path;
}
