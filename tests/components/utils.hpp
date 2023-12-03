#pragma once

#include <string>
#include <format>

#include <components/components.hpp>

std::string repr_mod_load_error(const core::components::LoadModError& err) {
	struct {
		std::string operator()(const core::components::InvalidFileError& err) {
			return std::format("Could not open file:\n\t {}", err.err);
		}

		std::string operator()(const core::components::LackingMethodError& err) {
			return std::format("{} method not present: {}", err.name, err.err);
		}
	} visitor;
	return std::visit(visitor, err);
}
