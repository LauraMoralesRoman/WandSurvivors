#include "handler.hpp"
#include <format>
#include <variant>

core::components::DynLibHandler::DynLibHandler(const std::string& path)
	: handle(dlopen(path.c_str(), RTLD_LAZY)) {
}

core::components::DynLibHandler::~DynLibHandler() {
	if (self->handle != nullptr) {
		dlclose(self->handle);
	}
}

core::components::DynLibHandler::operator Handler_t() const {
	return self->handle;
}

core::components::DynLibHandler::operator bool() const {
	return self->handle != nullptr;
}

// Repr
std::string core::components::func_load_err_repr(const FuncLoadErr& err) {
	struct {
		std::string operator()(const LoadFailedErr& err) {
			return std::format("Failed to load function:\n{}", err.err);
		}

		std::string operator()(const LibNotLoadedErr& err) {
			return "Library is not loaded, so no functions can be loaded";
		}
	} visitor;

	return std::visit(visitor, err);
}
