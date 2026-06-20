#include "User.h"
#include "../Constants.h"
#include "CalorixExceptions.h"

using namespace Constants;

unsigned User::nextId = Global::STARTING_ID;

User::User(const std::string& username, const Password& password, const UserProfile& profile)
    : userId(nextId++), username(username),
      password(password), profile(profile) {

    if (this->username.empty() || this->username == Global::EMPTY_STRING) {
        throw InvalidNameException("Username cannot be empty.");
    }
}

User::User(unsigned id, const std::string& username, const Password& password, const UserProfile& profile)
    : userId(id), username(username),
      password(password), profile(profile) {

    if (this->username.empty() || this->username == Global::EMPTY_STRING) {
        throw InvalidNameException("Username cannot be empty.");
    }
}

void User::updateNextId(unsigned loadedId) {
    if (loadedId >= nextId) {
        nextId = loadedId + 1;
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

UserProfile& User::getProfile() {
    return profile;
}

void User::setPassword(const Password& newPassword) {
    password = newPassword;
}

void User::setProfile(const UserProfile& newProfile) {
    profile = newProfile;
}