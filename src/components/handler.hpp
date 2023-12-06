#pragma once

#include "defs.hpp"
#include "result.hpp"
#include <dlfcn.h>
#include <functional>
#include <string>
#include <variant>

namespace core::components {
	struct LoadFailedErr {
		std::string err;
	};
	struct LibNotLoadedErr {};
	using FuncLoadErr = std::variant<LoadFailedErr, LibNotLoadedErr>;

	template <typename T>
	using FuncLoadResult = Result<std::function<T>, FuncLoadErr>;

	std::string func_load_err_repr(const FuncLoadErr& err);

	class DynLibHandler {
		using Handler_t = void*;
		public:
			DynLibHandler(const std::string& path);
			~DynLibHandler();

			explicit operator Handler_t() const;
			operator bool() const;

			template <typename T>
			FuncLoadResult<T> sym(const std::string& sym_name) {
				if (self->handle == nullptr) {
					return {LibNotLoadedErr{}};
				} else {
					auto f_ptr = reinterpret_cast<T*>(dlsym(self->handle, sym_name.c_str()));

					if (f_ptr == nullptr) {
						return {LoadFailedErr{dlerror()}};
					} else {
						return {std::function<T>{f_ptr}};
					}
				}
			}

			const Handler_t handle;
	};
}
