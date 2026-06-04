#pragma once
#include "ICalorieCalculator.h"

class WHOStrategy : public ICalorieCalculator {
public:
    double calculateBMR(const UserProfile& profile) const override;
};