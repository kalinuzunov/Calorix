#pragma once
#include "UserProfile.h"
#include "Enums.h"

class UserProfileBuilder {
private:
    double weight;
    double height;
    unsigned age;
    Gender gender;
    ActivityLevel activityLevel;

public:
    UserProfileBuilder();

    UserProfileBuilder& setWeight(double newWeight);
    UserProfileBuilder& setHeight(double newHeight);
    UserProfileBuilder& setAge(unsigned newAge);
    UserProfileBuilder& setGender(Gender newGender);
    UserProfileBuilder& setActivityLevel(ActivityLevel newActivityLevel);

    UserProfile build() const;
};