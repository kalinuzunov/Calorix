#pragma once
#include "ICalorieCalculator.h"

class HarrisBenedictStrategy : public ICalorieCalculator {
public:
    double calculateBMR(const UserProfile& profile) const override;
};