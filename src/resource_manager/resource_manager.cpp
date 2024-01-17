#include "resource_manager.hpp"

#include "raylib.h"
#include <algorithm>
#include <future>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace rg = std::ranges;

// ========
// Textures
// ========
const std::filesystem::path core::resources::Texture::location = get_resource_location(std::vector<std::string>{
	"textures"
});
const std::filesystem::path core::resources::Texture::default_path 
	= location / "default.png";

const core::resources::Texture core::resources::Texture::default_resource(Texture::default_path);

core::resources::Texture::Texture(const std::string& path) 
	: texture(LoadTexture(path.c_str())) {
}

core::resources::Texture::~Texture() {
	UnloadTexture(this->texture);
}

bool core::resources::Texture::valid() const {
	return this->texture.id != 0;
}

// ===================
// Other functionality
// ===================
std::filesystem::path core::resources::get_resource_location_base(std::string base_path, const std::vector<std::string> &&paths) {
	std::vector<std::string> paths_with_prefix {
		base_path
	};
	std::copy(paths.begin(), paths.end(), std::back_inserter(paths_with_prefix));

	return rg::fold_left(paths, std::filesystem::path{},
		[](const auto& accumulated, const auto& path) {
			return accumulated / path;
		}
	);
}

// ======================
// Async resource manager
// ======================
template<core::resources::Resource Base>
core::resources::AsyncResource<Base>::AsyncResource(const std::string& path)
	: path(path) {
	// Check if the resource has been asked for before
	if (!check_cache_hit()) {
		auto res_future = std::async([&]() {
			return Base(path);
		});
		this->cached_resources.insert({
			path,
			res_future.share()
		});
	}
};

template<core::resources::Resource Base>
core::resources::AsyncResource<Base>::operator Base&() {
	if (this->loaded_resource != nullptr) {
		return *loaded_resource;
	} else {
		if (check_cache_hit() && this->loaded_resource != nullptr) { // Shouldn't be nullptr anymore
			return *this->loaded_resource;
		} else {
			return Base::default_resource;
		}
	}
}

template<core::resources::Resource Base>
bool core::resources::AsyncResource<Base>::check_cache_hit() {
	auto& iter = this->cached_resources.find(this->path);
	if (iter != this->cached_resources.end()) { // Found
		auto& [key, resource] = *iter;
		if (resource.valid()) {
			this->loaded_resource = &resource.get();
		}
		return true;
	}
	return false;
}

template<> class core::resources::AsyncResource<core::resources::Texture>;
// template class core::resources::AsyncResource<core::resources::Audio>;
