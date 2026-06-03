#include "UserProfileBuilder.h"
#include "../Constants.h"

using namespace Constants;

UserProfileBuilder::UserProfileBuilder()
    : weight(ProfileDefaults::WEIGHT),
      height(ProfileDefaults::HEIGHT),
      age(ProfileDefaults::AGE),
      gender(Gender::OTHER),
      activityLevel(ActivityLevel::SEDENTARY) {
}

UserProfileBuilder& UserProfileBuilder::setWeight(double newWeight) {
    this->weight = newWeight;
    return *this;
}

UserProfileBuilder& UserProfileBuilder::setHeight(double newHeight) {
    this->height = newHeight;
    return *this;
}

UserProfileBuilder& UserProfileBuilder::setAge(unsigned newAge) {
    this->age = newAge;
    return *this;
}

UserProfileBuilder& UserProfileBuilder::setGender(Gender newGender) {
    this->gender = newGender;
    return *this;
}

UserProfileBuilder& UserProfileBuilder::setActivityLevel(ActivityLevel newActivityLevel) {
    this->activityLevel = newActivityLevel;
    return *this;
}

UserProfile UserProfileBuilder::build() const {
    return UserProfile(weight, height, age, gender, activityLevel);
}