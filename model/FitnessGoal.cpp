#include "FitnessGoal.h"
#include "../Constants.h"

using namespace Constants;

FitnessGoal::FitnessGoal()
    : type(GoalType::NONE), targetValue(0.0), deadline(Date()) {}

FitnessGoal::FitnessGoal(GoalType type, double targetValue, const Date& deadline)
    : type(type), targetValue(targetValue), deadline(deadline) {}

GoalType FitnessGoal::getType() const {
    return type;
}

double FitnessGoal::getTargetValue() const {
    return targetValue;
}

Date FitnessGoal::getDeadline() const {
    return deadline;
}