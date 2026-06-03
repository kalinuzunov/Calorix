#pragma once
#include "UserProfile.h"
#include "Password.h"
#include "Enums.h"
#include <string>

class UserBuilder {
private:
    std::string username;
    Password password;

    unsigned age;
    double weight;
    double height;
    Gender gender;
    ActivityLevel activityLevel;

public:
    UserBuilder(const std::string& username, const Password& password);

    UserBuilder& setAge(unsigned age);
    UserBuilder& setWeight(double weight);
    UserBuilder& setHeight(double height);
    UserBuilder& setGender(Gender gender);
    UserBuilder& setActivityLevel(ActivityLevel activityLevel);

    UserProfile buildProfile() const;
};