#pragma once

#include <memory>
#include <string>

#include "managers/UserManager.h"
#include "managers/FoodManager.h"
#include "managers/RecipeManager.h"
#include "managers/ExerciseManager.h"
#include "managers/BlockedUserManager.h"

#include "model/User.h"
#include "model/Enums.h"
#include "model/Date.h"

class CalorixSystem {
private:
    UserManager userManager;
    FoodManager foodManager;
    RecipeManager recipeManager;
    ExerciseManager exerciseManager;
    BlockedUserManager blockedUserManager;

    std::shared_ptr<User> currentUser;

public:
    CalorixSystem(const std::string& usersFile, const std::string& foodsFile,
                      const std::string& recipesFile, const std::string& exercisesFile,
                      const std::string& blockedUsersFile);

    void loginUser(const std::string& username, const std::string& password);
    void registerUser(const std::string& username, const std::string& password,
                      unsigned age, double weight, double height, Gender gender);
    void logoutUser();

    void initialize()const;
    void displayHelp() const;
    void shutdown();

    void blockUser(const std::string& targetUsername);
    void addFood(const std::string& name, double calories, double protein, double carbs, double fat, double fiber) const;
    void displayAllFoods() const;
    void updateFood(const std::string& foodName, double newCalories);
    void addExercise(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup);
    void displayAllExercises() const;

    void setGoal(GoalType type, double targetValue, const Date& deadline);
    void logFood(const std::string& foodName, double quantityGrams);
    void logExercise(const std::string& exerciseName, int durationMinutes);
    void viewDailySummary() const;
    void viewProgress() const;
    void calculateBMI() const;
    void calculateBMR() const;
    void generateWorkoutPlan(int durationMinutes) const;
    void addToFavorites(const std::string& exerciseName);
    void viewFavorites() const;
};