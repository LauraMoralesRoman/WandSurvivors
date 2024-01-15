#pragma once

#include "components/manager.hpp"
#include "utils/metafunctions.hpp"
#include "utils/type_map.hpp"
#include <string>
#include <type_traits>

namespace core::components {

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

	///////////////////
	// Entity manager / 
	///////////////////
	template<typename GameEntities>
	using BaseType = metafunc::ApplyListToType<GameEntities, EntityManager>::type;

	template<typename GameEntities>
	class GameEntityManager 
		: public BaseType<GameEntities>
	{
		public:
			GameEntityManager(const utils::TypeMap<std::string>& module_map) 
				: BaseType<GameEntities>(module_map) {

			}

			void remove_marked() {
				metafunc::for_each_in_tuple(self->specific_managers, [](auto& manager) {
					manager.remove_marked();
				});
			}

			void reload_all();

			template<typename T>
			void reload() {
				std::get<T>(self->specific_managers).reload();
			}
	};
}
