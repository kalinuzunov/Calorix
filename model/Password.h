#pragma once
#include <string>

class Password {
private:
    std::string value;

    bool hasUpperCase(const std::string& str) const;
    bool hasLowerCase(const std::string& str) const;
    bool hasDigit(const std::string& str) const;
    bool hasSpecialChar(const std::string& str) const;
    bool isValid(const std::string& str) const;

public:
    Password();
    Password(const std::string& passwordString);

    std::string getValue() const;
    void setValue(const std::string& newPasswordString);
};