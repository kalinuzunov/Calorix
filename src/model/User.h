#pragma once
#include <string>
#include <memory>
#include "UserProfile.h"

class User {
private:
    UserProfile profile;   
    std::string username;  
    std::string password;  
    static unsigned nextId;
    unsigned userId;     

public:
    User(const std::string& username, const std::string& password, const UserProfile& profile);

    virtual ~User() = default;

    virtual void printHelp() const = 0;
    virtual std::unique_ptr<User> clone() const = 0;

    unsigned getUserId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    UserProfile getProfile() const;

    void setPassword(const std::string& newPassword);
    void setProfile(const UserProfile& newProfile);
};