#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <result.hpp>
#include <variant>

#include <dlfcn.h>

#include <defs.hpp>

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
		std::function<C*()> instantiate;
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
		auto handler = dlopen(path.c_str(), RTLD_LAZY);
		if (!handler) {
			return {InvalidFileError(dlerror())};
		}

		auto instantiate = reinterpret_cast<C*(*)()>(dlsym(handler, "instantiate"));
		if (!instantiate) {
			return {LackingMethodError{
				.name = "instantiate", 
				.err = dlerror()
			}};
		}

		mod.instantiate = {instantiate};

		return {mod};
	}

	template <typename C>
	ReloadResult<C> reload_module(const Module<C> mod) {
		auto load_res = load_module<C>(mod.path);
		struct {
			const Module<C>& prev_mod;
			ReloadResult<C> operator()(const Module<C>& mod) {
				return {mod};
			}

			ReloadResult<C> operator() (const LoadModError& err) {
				return {ReloadError<C>{
					.prev_module = prev_mod,
					.err = err
				}};
			}
		} visitor{
			.prev_mod = mod
		};

		return std::visit(visitor, load_res);
	}
}
