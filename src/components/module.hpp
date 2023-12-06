#pragma once

#include "component.hpp"
#include "components/handler.hpp"
#include <algorithm>
#include <bits/ranges_base.h>
#include <cstdint>
#include <functional>
#include <string>
#include <result.hpp>
#include <variant>
#include <memory>


#include <dlfcn.h>

#include <defs.hpp>
#include <iterator.hpp>

namespace core::components {
	//////////////////////
	// Type definitions //
	//////////////////////
		// Errors
	struct InvalidFileError {
		std::string err;
	};

	struct LackingMethodError {
		std::string name;
		std::string err;
	};
		//////////

	template <typename C>
	struct Module {
		std::string path;
		std::function<std::unique_ptr<C>()> instantiate;
		std::shared_ptr<DynLibHandler> handle;
	};

	// Result types
	using LoadModError = std::variant<InvalidFileError, LackingMethodError>;
	template <typename C>
	struct ReloadError {
		LoadModError err;
		Module<C> prev_module;
	};

	template <typename C>
	using LoadResult = Result<Module<C>, LoadModError>;
	template <typename C>
	using ReloadResult = Result<Module<C>, ReloadError<C>>;


	//////////////////////////
	// Function definitions //
	//////////////////////////
	template <typename C>
	LoadResult<C> load_module(const std::string& path) {
		Module<C> mod;
		mod.path = path;
		// Try load the library
		std::shared_ptr handle = std::make_shared<DynLibHandler>(path);
		if (!*handle) {
			return {InvalidFileError(dlerror())};
		}

		mod.handle = handle;

		auto instantiate_res = handle->sym<C*()>("instantiate");
		if (!instantiate_res.valid()) {
			return {LackingMethodError{
				.name = "instantiate", 
				.err = func_load_err_repr(instantiate_res.error())
			}};
		}
		auto instantiate = instantiate_res.value();

		mod.instantiate = {[=]() -> std::unique_ptr<C> {
			return std::unique_ptr<C>(instantiate());
		}};

		return {mod};
	}

	template <typename C>
	ReloadResult<C> reload_module(const Module<C>& mod) {
		auto load_res = load_module<C>(mod.path);
		if (load_res.valid()) {
			return {load_res.value()};
		} else {
			return {ReloadError<C>{
				.err = load_res.error(),
				.prev_module = mod
			}};
		}
	}

	/**
	 * Replaces the vtables in a collection of type Collection<unique_ptr<C>>
	 */
	template <typename C>
	void set_vtables(const Module<C>& mod, auto& container) {
		// Get vtable
		auto instance = mod.instantiate();
		auto new_vtable = *reinterpret_cast<uintptr_t*>(instance.get());

		for (auto& val : container) {
			auto* as_ptr = reinterpret_cast<uintptr_t*>(val.get());
			*as_ptr = new_vtable;
		}
	}
}
