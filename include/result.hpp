#pragma once

#include <stdexcept>
#include <variant>

template <typename Ok, typename Err>
class Result {
private:
    std::variant<Ok, Err> value_or_error;

public:
    // Constructors
    Result(const Ok& value) : value_or_error(value) {}
    Result(Ok&& value) : value_or_error(std::move(value)) {}
    Result(const Err& error) : value_or_error(error) {}
    Result(Err&& error) : value_or_error(std::move(error)) {}

    // Check if it has a value (valid)
    bool valid() const noexcept {
        return std::holds_alternative<Ok>(value_or_error);
    }

    // Get the value or throw an exception
    Ok& value() {
        if (!valid()) {
            throw std::logic_error("Tried to get Ok variant in Result when Error was present");
        }
        return std::get<Ok>(value_or_error);
    }
    const Ok& value() const {
        if (!valid()) {
            throw std::logic_error("Tried to get Ok variant in Result when Error was present");
        }
        return std::get<Ok>(value_or_error);
    }

    // Get the error
    Err& error() {
        if (valid()) {
            throw std::logic_error("No error present, valid value exists");
        }
        return std::get<Err>(value_or_error);
    }
    const Err& error() const {
        if (valid()) {
            throw std::logic_error("No error present, valid value exists");
        }
        return std::get<Err>(value_or_error);
    }

    // Optional-like value extraction
    Ok value_or(Ok&& default_value) const {
        return valid() ? value() : default_value;
    }
};
