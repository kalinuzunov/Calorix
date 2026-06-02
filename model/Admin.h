#pragma once
#include "User.h"
#include "Enums.h"
#include <string>

class Admin : public User {
public:
    Admin(const std::string& username, const std::string& password, const UserProfile& profile);

    void blockUser(const std::string& targetUsername);

    void addFood(const std::string& name, double caloriesPer100g, double proteinPer100g, 
                 double carbsPer100g, double fatPer100g, double fiberPer100g);
                 
    void addExercise(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup);
    
    void updateFood(const std::string& foodName, double newCalories);
};