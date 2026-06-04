#include "HarrisBenedictStrategy.h"
#include "../Constants.h"

using namespace Constants;

double HarrisBenedictStrategy::calculateBMR(const UserProfile& profile) const {
    double w = profile.getWeight();
    double h = profile.getHeight();
    unsigned a = profile.getAge();
    int gIndex = static_cast<int>(profile.getGender());

    return HealthFormulas::HarrisBenedict::BASE[gIndex] +
          (HealthFormulas::HarrisBenedict::WEIGHT_MULT[gIndex] * w) +
          (HealthFormulas::HarrisBenedict::HEIGHT_MULT[gIndex] * h) -
          (HealthFormulas::HarrisBenedict::AGE_MULT[gIndex] * a);
}