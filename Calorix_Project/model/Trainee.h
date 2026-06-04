#pragma once
#include "User.h"
#include "FoodEntry.h"
#include "ExerciseEntry.h"
#include "FitnessGoal.h"
#include "ICalorieCalculator.h"
#include <vector>
#include <memory>

class Trainee : public User {
private:
    std::vector<FoodEntry> foodDiary;
    std::vector<ExerciseEntry> exerciseDiary;
    std::vector<unsigned> favoriteExercises;
    FitnessGoal goal;

    std::unique_ptr<ICalorieCalculator> calculator;

public:
    Trainee(const std::string& username, const Password& password, const UserProfile& profile);
    Trainee(unsigned id, const std::string& username, const Password& password, const UserProfile& profile);

    void setCalorieCalculator(std::unique_ptr<ICalorieCalculator> newCalculator);

    void logFood(const FoodEntry& entry);
    void logExercise(const ExerciseEntry& entry);

    void addFavoriteExercise(unsigned exerciseId);
    void removeFavoriteExercise(unsigned exerciseId);

    void setFitnessGoal(const FitnessGoal& newGoal);
    const FitnessGoal& getFitnessGoal() const;

    const std::vector<FoodEntry>& getFoodDiary() const;
    const std::vector<ExerciseEntry>& getExerciseDiary() const;
    const std::vector<unsigned>& getFavoriteExercises() const;

    double calculateBMI() const;
    double calculateBMR() const;
    double calculateDailyCalorieTarget() const;
};