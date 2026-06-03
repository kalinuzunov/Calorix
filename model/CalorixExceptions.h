#pragma once
#include <stdexcept>
#include <string>

class InvalidPasswordException : public std::invalid_argument {
public:
    explicit InvalidPasswordException(const std::string& message)
        : std::invalid_argument("Password Error: " + message) {}
};

class InvalidDateException : public std::invalid_argument {
public:
    explicit InvalidDateException(const std::string& message)
        : std::invalid_argument("Date Error: " + message) {}
};

class InvalidWeightException : public std::invalid_argument {
public:
    explicit InvalidWeightException(const std::string& message)
        : std::invalid_argument("Weight/Quantity Error: " + message) {}
};
    class InvalidNameException : public std::invalid_argument {
    public:
        explicit InvalidNameException(const std::string& message)
            : std::invalid_argument("Naming Error: " + message) {}
    };

    class InvalidMacroException : public std::invalid_argument {
    public:
        explicit InvalidMacroException(const std::string& message)
            : std::invalid_argument("Macronutrient/Calories Error: " + message) {}
    };
