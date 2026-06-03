#include "Admin.h"
#include "FoodBuilder.h"
#include "CalorixExceptions.h"
#include "../Constants.h"

Admin::Admin(const std::string& username, const Password& password, const UserProfile& profile)
    : User(username, password, profile) {
}

Food Admin::addFood(const std::string& name, double caloriesPer100g, double proteinPer100g,
                    double carbsPer100g, double fatPer100g, double fiberPer100g) const {

    FoodBuilder builder(name);
    return builder.setCalories(caloriesPer100g)
                  .setProtein(proteinPer100g)
                  .setCarbs(carbsPer100g)
                  .setFat(fatPer100g)
                  .setFiber(fiberPer100g)
                  .build();
}

Exercise Admin::addExercise(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup) const {
    return Exercise(name, caloriesBurnedPerHour, muscleGroup);
}

std::string Admin::blockUser(const std::string& targetUsername) const {
    if (targetUsername.empty() || targetUsername == Constants::Global::EMPTY_STRING) {
        throw InvalidNameException("Target username cannot be empty.");
    }
    if (targetUsername == getUsername()) {
        throw std::invalid_argument("An admin cannot block themselves.");
    }

    return targetUsername;
}

std::pair<std::string, double> Admin::updateFood(const std::string& foodName, double newCalories) const {
    if (foodName.empty() || foodName == Constants::Global::EMPTY_STRING) {
        throw InvalidNameException("Food name cannot be empty.");
    }
    if (newCalories < Constants::FoodLimits::DEFAULT_MACRO_VALUE) {
        throw InvalidMacroException("Updated calories cannot be negative.");
    }

    return {foodName, newCalories};
}