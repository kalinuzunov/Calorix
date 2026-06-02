#include "User.h"
#include "../Constants.h"
#include <stdexcept>

unsigned User::nextId = 1;

User::User(const std::string& username, const std::string& password, const UserProfile& profile)
    : profile(profile), username(username), userId(nextId++) {

    if (this->username.empty()) {
        throw std::invalid_argument("Username cannot be empty.");
    }

    setPassword(password);
}

unsigned User::getUserId() const { 
    return userId; }
std::string User::getUsername() const {
    return username; }
std::string User::getPassword() const {
    return password; }
UserProfile User::getProfile() const {
    return profile; }

void User::setPassword(const std::string& newPassword) {
    if (newPassword.length() < Constants::UserLimits::MIN_PASSWORD_LENGTH) {
        throw std::invalid_argument("Password is too short.");
    }
    password = newPassword;
}

void User::setProfile(const UserProfile& newProfile) {
    profile = newProfile;
}