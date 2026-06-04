#pragma once
#include "UserProfile.h"

class ICalorieCalculator {
public:
    virtual ~ICalorieCalculator() = default;

    virtual double calculateBMR(const UserProfile& profile) const = 0;
};