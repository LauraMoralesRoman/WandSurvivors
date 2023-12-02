#pragma once

#include <stdexcept>
#include <variant>

template <typename Ok, typename Err>
class Result {
private:
    std::variant<Ok, Err> value_or_error;
    bool has_value;

public:
    // Constructores
    Result(const Ok& value) : value_or_error(value), has_value(true) {}
    Result(const Err& error) : value_or_error(error), has_value(false) {}

    // Verifica si tiene valor
    bool valid() const { return has_value; }

    // Obtener el valor o lanzar una excepción si hay un error
    Ok& value() {
        if (!has_value) {
            throw std::logic_error("Tried to get Ok variant in Result when Error was present");
        }
        return std::get<Ok>(value_or_error);
    }

    // Obtener el error
    Err& error() {
        if (has_value) {
            throw std::logic_error("No error present, valid value exists");
        }
        return std::get<Err>(value_or_error);
    }
};
