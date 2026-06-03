#pragma once
#include "User.h"
#include "Enums.h"
#include "Food.h"
#include "Exercise.h"
#include <string>
#include <utility>

class Admin : public User {
public:
    Admin(const std::string& username, const Password& password, const UserProfile& profile);

    Food addFood(const std::string& name, double caloriesPer100g, double proteinPer100g,
                 double carbsPer100g, double fatPer100g, double fiberPer100g) const;

    Exercise addExercise(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup) const;

    std::string blockUser(const std::string& targetUsername) const;
    std::pair<std::string, double> updateFood(const std::string& foodName, double newCalories) const;
};