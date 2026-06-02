#include "User.h"
#include "../Constants.h"
#include <stdexcept>

using namespace Constants;

unsigned User::nextId = 1;

User::User(const std::string& username, const Password& password, const UserProfile& profile)
    : profile(profile), username(username), password(password), userId(nextId++) {
    if (this->username.empty()) {
        throw std::invalid_argument("Username cannot be empty.");
    }
}

unsigned User::getUserId() const {
    return userId;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password.getValue();
}

UserProfile User::getProfile() const {
    return profile;
}

void User::setPassword(const Password& newPassword) {
    password = newPassword;
}

void User::setProfile(const UserProfile& newProfile) {
    profile = newProfile;
}