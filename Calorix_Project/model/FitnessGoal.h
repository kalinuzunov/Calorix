#pragma once
#include "Enums.h"
#include "Date.h"

class FitnessGoal {
private:
    GoalType type;
    double targetValue;
    Date startDate;
    Date deadline;
    bool isAchieved;

public:
    FitnessGoal();

    FitnessGoal(GoalType type, double targetValue, const Date& startDate, const Date& deadline);

    GoalType getType() const;
    double getTargetValue() const;
    Date getStartDate() const;
    Date getDeadline() const;
    bool getIsAchieved() const;

    void setAchieved(bool status);
};