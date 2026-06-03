#include "FitnessGoal.h"
#include "../Constants.h"
#include "CalorixExceptions.h"

using namespace Constants;

FitnessGoal::FitnessGoal()
    : type(GoalType::NONE),
      targetValue(GoalLimits::DEFAULT_TARGET_VALUE),
      deadline(Date()) {}

FitnessGoal::FitnessGoal(GoalType type, double targetValue, const Date& deadline)
    : type(type), targetValue(targetValue), deadline(deadline) {

    if (this->type == GoalType::WEIGHT_LOSS || this->type == GoalType::BULKING) {
        if (this->targetValue <= ProfileLimits::MIN_WEIGHT) {
            throw InvalidWeightException("Target value for the fitness goal must be strictly positive.");
        }
    }
}

GoalType FitnessGoal::getType() const {
    return type;
}

double FitnessGoal::getTargetValue() const {
    return targetValue;
}

Date FitnessGoal::getDeadline() const {
    return deadline;
}