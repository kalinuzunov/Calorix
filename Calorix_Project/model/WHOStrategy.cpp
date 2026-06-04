#include "WHOStrategy.h"
#include "../Constants.h"

using namespace Constants;

double WHOStrategy::calculateBMR(const UserProfile& profile) const {
    double w = profile.getWeight();
    unsigned age = profile.getAge();
    Gender gender = profile.getGender();

    if (gender == Gender::MALE || gender == Gender::OTHER) {
        if (age <= HealthFormulas::WHO::AGE_YOUNG) {
            return (HealthFormulas::WHO::MALE_18_30_MULT * w) + HealthFormulas::WHO::MALE_18_30_BASE;
        } else if (age <= HealthFormulas::WHO::AGE_MIDDLE) {
            return (HealthFormulas::WHO::MALE_31_60_MULT * w) + HealthFormulas::WHO::MALE_31_60_BASE;
        } else {
            return (HealthFormulas::WHO::MALE_60_PLUS_MULT * w) + HealthFormulas::WHO::MALE_60_PLUS_BASE;
        }
    } 
    else {
        if (age <= HealthFormulas::WHO::AGE_YOUNG) {
            return (HealthFormulas::WHO::FEMALE_18_30_MULT * w) + HealthFormulas::WHO::FEMALE_18_30_BASE;
        } else if (age <= HealthFormulas::WHO::AGE_MIDDLE) {
            return (HealthFormulas::WHO::FEMALE_31_60_MULT * w) + HealthFormulas::WHO::FEMALE_31_60_BASE;
        } else {
            return (HealthFormulas::WHO::FEMALE_60_PLUS_MULT * w) + HealthFormulas::WHO::FEMALE_60_PLUS_BASE;
        }
    }
}