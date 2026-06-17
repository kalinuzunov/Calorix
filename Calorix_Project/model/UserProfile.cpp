#include "UserProfile.h"
#include "../Constants.h"
#include "CalorixExceptions.h"

UserProfile::UserProfile()
    : weight(Constants::ProfileDefaults::WEIGHT),height(Constants::ProfileDefaults::HEIGHT),
      age(Constants::ProfileDefaults::AGE),gender(Gender::OTHER),
      activityLevel(ActivityLevel::SEDENTARY) {
}

UserProfile::UserProfile(double weight, double height, unsigned age, Gender gender, ActivityLevel activityLevel) {
    setWeight(weight);
    setHeight(height);
    setAge(age);
    setGender(gender);
    setActivityLevel(activityLevel);
}

double UserProfile::getWeight() const {
    return weight;
}
double UserProfile::getHeight() const {
    return height;
}
unsigned UserProfile::getAge() const {
    return age;
}
Gender UserProfile::getGender() const {
    return gender;
}
ActivityLevel UserProfile::getActivityLevel() const { return activityLevel; }

void UserProfile::setWeight(double newWeight) {
    if (newWeight <= Constants::ProfileLimits::MIN_WEIGHT) {
        throw InvalidWeightException("Weight must be positive.");
    }
    weight = newWeight;
}

void UserProfile::setHeight(double newHeight) {
    if (newHeight <= Constants::ProfileLimits::MIN_HEIGHT) {
        throw InvalidWeightException("Height must be positive.");
    }
    height = newHeight;
}

void UserProfile::setAge(unsigned newAge) {
    if (newAge < Constants::ProfileLimits::MIN_AGE || newAge > Constants::ProfileLimits::MAX_AGE) {
        throw InvalidDateException("Age is outside valid boundaries.");
    }
    age = newAge;
}

void UserProfile::setGender(Gender newGender) {
    gender = newGender;
}

void UserProfile::setActivityLevel(ActivityLevel newActivityLevel) {
    activityLevel = newActivityLevel;
}