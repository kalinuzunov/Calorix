#include "UserBuilder.h"
#include "../Constants.h"

using namespace Constants;

UserBuilder::UserBuilder(const std::string& username, const Password& password)
    : username(username),
      password(password),
      age(UserLimits::DEFAULT_AGE),
      weight(FoodLimits::DEFAULT_MACRO_VALUE),
      height(FoodLimits::DEFAULT_MACRO_VALUE),
      gender(Gender::UNKNOWN),
      activityLevel(ActivityLevel::SEDENTARY) {}

UserBuilder& UserBuilder::setAge(unsigned age) {
    this->age = age;
    return *this;
}

UserBuilder& UserBuilder::setWeight(double weight) {
    this->weight = weight;
    return *this;
}

UserBuilder& UserBuilder::setHeight(double height) {
    this->height = height;
    return *this;
}

UserBuilder& UserBuilder::setGender(Gender gender) {
    this->gender = gender;
    return *this;
}

UserBuilder& UserBuilder::setActivityLevel(ActivityLevel activityLevel) {
    this->activityLevel = activityLevel;
    return *this;
}

UserProfile UserBuilder::buildProfile() const {
    return UserProfile(age, weight, height, gender, activityLevel);
}