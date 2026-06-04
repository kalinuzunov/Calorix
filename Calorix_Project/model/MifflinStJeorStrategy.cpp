#include "MifflinStJeorStrategy.h"
#include "../Constants.h"

using namespace Constants;

double MifflinStJeorStrategy::calculateBMR(const UserProfile& profile) const {
    double weight = profile.getWeight();
    double height = profile.getHeight();
    unsigned age = profile.getAge();
    Gender gender = profile.getGender();

    double base = (HealthFormulas::MifflinStJeor::WEIGHT_MULTIPLIER * weight) +
                  (HealthFormulas::MifflinStJeor::HEIGHT_MULTIPLIER * height) -
                  (HealthFormulas::MifflinStJeor::AGE_MULTIPLIER * age);

    return base + HealthFormulas::MifflinStJeor::MODIFIERS[static_cast<int>(gender)]; 
}