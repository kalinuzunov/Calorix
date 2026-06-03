#include "User.h"
#include "../Constants.h"
#include <stdexcept>

using namespace Constants;

unsigned User::nextId = Global::STARTING_ID;

User::User(const std::string& username, const Password& password, const UserProfile& profile)
    : profile(profile), username(username), password(password), userId(nextId++) {
    if (this->username.empty()) {
        throw std::invalid_argument("Username cannot be empty.");
    }
}

unsigned User::getUserId() const {
    return userId;
}

const std::string& User::getUsername() const {
    return username;
}

const std::string& User::getPassword() const {
    return password.getValue();
}

const UserProfile& User::getProfile() const {
    return profile;
}

void User::setPassword(const Password& newPassword) {
    password = newPassword;
}

void User::setProfile(const UserProfile& newProfile) {
    profile = newProfile;
}