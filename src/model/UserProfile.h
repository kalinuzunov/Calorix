#pragma once
#include "Enums.h"

class UserProfile {
private:
    double weight;
    double height;
    unsigned age;
    Gender gender;
    ActivityLevel activityLevel;

public:
    UserProfile();
    UserProfile(double weight, double height, unsigned age, Gender gender, ActivityLevel activityLevel);

    double getWeight() const;
    double getHeight() const;
    unsigned getAge() const;
    Gender getGender() const;
    ActivityLevel getActivityLevel() const;

    void setWeight(double newWeight);
    void setHeight(double newHeight);
    void setAge(unsigned int newAge);
    void setGender(Gender newGender);
    void setActivityLevel(ActivityLevel newActivityLevel);
};