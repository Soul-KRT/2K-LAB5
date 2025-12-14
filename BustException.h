#pragma once
#include <stdexcept>

class BustException : public std::runtime_error {
public:
    BustException() : std::runtime_error("Перебор!") {}
};
