#pragma once

#include "components/manager.hpp"
#include "utils/metafunctions.hpp"
#include <string>
#include <type_traits>

namespace core::components {

	using GameEntities = metafunc::TypeList<
		// Add Game Entities here
	>;

	namespace meta {
		template<typename, typename T>
		struct go_mapping_exist : std::false_type {};

		template<typename T>
		struct go_mapping_exist<decltype((void)(T::value()), void()), T>
			: std::is_same<const std::string, decltype(T::value())> {};

		template<typename... Types>
		struct complete_go_mapping_coverage :
			metafunc::all_true<go_mapping_exist<void, Types>...> {};

		template<typename... Types>
		inline constexpr bool complete_go_mapping_coverage_v = complete_go_mapping_coverage<Types...>::type;
	}

	// Type Mapping
	template<typename T = void>
	struct EntityModules {};

	#define ENTRY(entity, path) \
	template<> struct EntityModules<entity> { \
		static_assert(metafunc::is_in_list_v<entity, GameEntities>); \
		static const std::string value() { return path; } \
	}

	// ENTRY(Test, "path/to/mod.so"); // Example of key-value maping
	#undef ENTRY

	static_assert(metafunc::ApplyListToType<
				GameEntities, 
				meta::complete_go_mapping_coverage
			>::type::value,
			"The type mapping should contain paths for all keys");

	///////////////////
	// Entity manager / 
	///////////////////
	/// I could pass this manager the GameObjects Type list but I don't wanna
	using BaseType = metafunc::ApplyListToType<GameEntities, EntityManager>::type;
	class GameEntityManager 
		: public BaseType
	{
		public:
			GameEntityManager();

			void remove_marked();
			void reload_all();

			template<typename T>
			void reload() {
				std::get<T>(self->specific_managers).reload();
			}
	};

	// I hate that C++ doesn't have modules yet and I have to create a class for this
	class GameComponentSystem {
		public:
			GameComponentSystem();

		private:
			GameEntityManager manager;
	};
}
