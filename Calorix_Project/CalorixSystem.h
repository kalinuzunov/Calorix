#pragma once

#include <memory>
#include <string>

#include "managers/UserManager.h"
#include "managers/FoodManager.h"
#include "managers/RecipeManager.h"
#include "managers/ExerciseManager.h"

#include "model/User.h"
#include "model/Enums.h"

class CalorixSystem {
private:
    UserManager userManager;
    FoodManager foodManager;
    RecipeManager recipeManager;
    ExerciseManager exerciseManager;

    std::shared_ptr<User> currentUser;

public:
    CalorixSystem(const std::string& usersFile, const std::string& foodsFile,
                      const std::string& recipesFile, const std::string& exercisesFile);

    void loginUser(const std::string& username, const std::string& password);
    void registerUser(const std::string& username, const std::string& password, 
                      unsigned age, double weight, double height, Gender gender);
    void logoutUser();

    void displayHelp() const;
    void shutdown();

    void blockUser(const std::string& targetUsername);
    void addFood(const std::string& name, double calories, double protein, double carbs, double fat, double fiber);
    void updateFood(const std::string& foodName, double newCalories);
    void addExercise(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup);
};