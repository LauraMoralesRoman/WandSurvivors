#pragma once
#include "raylib.h"
#include <functional>
#include <future>
#include <string>

#include <filesystem>
#include <type_traits>
#include <vector>


namespace core::resources {
	const auto RESOURCE_PATH = std::filesystem::path{"resources"};

	std::filesystem::path get_resource_location_base(std::string base_path, const std::vector<std::string>&& paths); 
	const auto get_resource_location = std::bind_front(get_resource_location_base, RESOURCE_PATH);

	template<typename T>
	concept Resource = requires (T t, const T ct) {
		std::is_same_v<decltype(T::location), std::filesystem::path>;
		std::is_same_v<decltype(T::default_path), std::filesystem::path>;
		std::is_same_v<decltype(T::default_resource), T>;

		{ ct.valid() } -> std::same_as<bool>;
		std::is_constructible_v<T, std::string>;
	};

	class Texture {
		public:
			Texture(const std::string& path);

			static const std::filesystem::path location;
			static const std::filesystem::path default_path;
			static const Texture default_resource;

			bool valid() const;

			const Texture2D texture;
	};

	class Audio {
		public:
	};

	template<Resource Base>
	class AsyncResource {
		public:
			AsyncResource(const std::string&& path);
			operator Base();

		private:
			std::future<Base> loaded_resource;
	};
}
