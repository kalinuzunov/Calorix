#pragma once
#include "ICalorieCalculator.h"

class MifflinStJeorStrategy : public ICalorieCalculator {
public:
    double calculateBMR(const UserProfile& profile) const override;
};