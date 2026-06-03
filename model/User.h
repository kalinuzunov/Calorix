#pragma once
#include <string>
#include "UserProfile.h"
#include "Password.h"

class User {
private:
    static unsigned nextId;
    unsigned userId;
    std::string username;
    Password password;
    UserProfile profile;

public:
    User(const std::string& username, const Password& password, const UserProfile& profile);
    virtual ~User() = default;

    unsigned getUserId() const;
    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const UserProfile& getProfile() const;

    void setPassword(const Password& newPassword);
    void setProfile(const UserProfile& newProfile);
};