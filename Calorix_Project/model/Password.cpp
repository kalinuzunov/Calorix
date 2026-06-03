#include "Password.h"
#include "../Constants.h"
#include "CalorixExceptions.h"
#include <cctype>

using namespace Constants;

bool Password::hasUpperCase(const std::string& str) const {
    for (char ch : str) {
        if (std::isupper(ch)) return true;
    }
    return false;
}

bool Password::hasLowerCase(const std::string& str) const {
    for (char ch : str) {
        if (std::islower(ch)) return true;
    }
    return false;
}

bool Password::hasDigit(const std::string& str) const {
    for (char ch : str) {
        if (std::isdigit(ch)) return true;
    }
    return false;
}

bool Password::hasSpecialChar(const std::string& str) const {
    for (char ch : str) {
        if (std::ispunct(ch)) return true;
    }
    return false;
}

bool Password::isValid(const std::string& str) const {
    return str.length() >= UserLimits::MIN_PASSWORD_LENGTH &&
           hasUpperCase(str) &&
           hasLowerCase(str) &&
           hasDigit(str) &&
           hasSpecialChar(str);
}

Password::Password() : value("") {}

Password::Password(const std::string& passwordString) {
    if (!isValid(passwordString)) {
        throw InvalidPasswordException("Password must contain at least 8 characters, including uppercase, lowercase, a digit, and a special character.");
    }
    value = passwordString;
}

const std::string& Password::getValue() const {
    return value;
}

void Password::setValue(const std::string& newPasswordString) {
    if (!isValid(newPasswordString)) {
        throw InvalidPasswordException("Password must contain at least 8 characters, including uppercase, lowercase, a digit, and a special character.");
    }
    value = newPasswordString;
}