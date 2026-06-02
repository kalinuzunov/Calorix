#pragma once
#include "Enums.h"
#include "Date.h"

class FitnessGoal {
private:
    GoalType type;
    double targetValue;
    Date deadline;

public:
    FitnessGoal();
    FitnessGoal(GoalType type, double targetValue, const Date& deadline);

    GoalType getType() const;
    double getTargetValue() const;
    Date getDeadline() const;
};