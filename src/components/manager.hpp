#pragma once

#include "components/entity.hpp"
#include "components/module.hpp"
#include "defs.hpp"
#include "result.hpp"
#include "spdlog/spdlog.h"
#include "utils/metafunctions.hpp"
#include "utils/type_map.hpp"

#include <algorithm>
#include <format>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace core::components {
	// Error management types
	template<typename C>
	class EntitySpecificManager;

	template<typename C>
	using LoadSpecificManagerResult = Result<EntitySpecificManager<C>, LoadModError>;
	
	template<typename C>
	class EntitySpecificManager {
		public:
			EntitySpecificManager(Module<C>& mod)
				: module(mod) {
			}

			static LoadSpecificManagerResult<C> create(LoadResult<C>&& res) {
				if (res.valid()) {
					return EntitySpecificManager<C>(res.value()); // Move directly into the result
				} else {
					return {res.error()};
				}
			}

			Entity<C>& instantiate() {
				auto instance = self->module.instantiate();
				Entity<C> entity; 
				entity.swap(instance);
				self->instances.push_back(std::move(entity));
				return self->instances.back();
			}

			auto size() {
				return self->instances.size();
			}

			auto remove_marked() {
				auto prev_len = self->instances.size();
				self->instances.erase(std::remove_if(
					self->instances.begin(),
					self->instances.end(),
					[](auto& instance) { return instance.is_marked(); }
				), self->instances.end());

				return prev_len - self->instances.size();
			}

		private:
			std::vector<Entity<C>> instances;
			Module<C> module;
	};

	// God forgive me for what I'm about to do
	namespace metafunctions {
		template<typename T>
		struct WrapEntitySpecificManagerMorph {
			using type = LoadSpecificManagerResult<T>;
		};
	}

	template<typename... ModTypes>
	class EntityManager {
		public:
			EntityManager(const utils::TypeMap<std::string>& module_map) 
				: specific_managers(create_specific_managers(module_map)) {
			}

			template<typename T>
			Entity<T>* instantiate() {
				static_assert(metafunc::is_in_list_v<T, ModTypes...>, "Type should be in the Manager defined list");

				auto& manager_res = std::get<typename metafunctions::WrapEntitySpecificManagerMorph<T>::type>(specific_managers);
				if (manager_res.valid()) {
					auto& manager = manager_res.value();
					return &(manager.instantiate());
				} else {
					spdlog::error("Trying to instantiate from an unloaded module"); // TODO: add better error message
					return nullptr;
				}
			}

		protected:
			metafunc::TransformTuple<std::tuple<ModTypes...>, metafunctions::WrapEntitySpecificManagerMorph>::type specific_managers;
		private:

			static auto create_specific_managers(const utils::TypeMap<std::string>& module_map) {
				return std::make_tuple(
					create_manager<ModTypes>(module_map.get<ModTypes>())...
				);
			}

			template<typename ModType>
			static auto create_manager(const utils::TypeMap<std::string>::Result& res) {
				if (res.has_value()) {
					return EntitySpecificManager<ModType>::create(
								load_module<ModType>(res.value())
							);
				} else {
					return EntitySpecificManager<ModType>::create({InvalidFileError{ 
						std::format("The specified Entity Type does not have a module associated")
					}});
				}
			}
	};
}
