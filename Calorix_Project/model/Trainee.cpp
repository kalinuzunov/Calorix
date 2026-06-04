#include "Trainee.h"
#include "../Constants.h"
#include <algorithm>

using namespace Constants;

Trainee::Trainee(const std::string& username, const Password& password, const UserProfile& profile)
    : User(username, password, profile) {
}

Trainee::Trainee(unsigned id, const std::string& username, const Password& password, const UserProfile& profile)
    : User(id, username, password, profile) {
}

void Trainee::setCalorieCalculator(std::unique_ptr<ICalorieCalculator> newCalculator) {
    calculator = std::move(newCalculator);
}

void Trainee::logFood(const FoodEntry& entry) {
    foodDiary.push_back(entry);
}

void Trainee::logExercise(const ExerciseEntry& entry) {
    exerciseDiary.push_back(entry);
}

void Trainee::addFavoriteExercise(unsigned exerciseId) {
    if (std::find(favoriteExercises.begin(), favoriteExercises.end(), exerciseId) == favoriteExercises.end()) {
        favoriteExercises.push_back(exerciseId);
    }
}

void Trainee::removeFavoriteExercise(unsigned exerciseId) {
    favoriteExercises.erase(
        std::remove(favoriteExercises.begin(), favoriteExercises.end(), exerciseId),
        favoriteExercises.end()
    );
}

void Trainee::setFitnessGoal(const FitnessGoal& newGoal) {
    goal = newGoal;
}

const FitnessGoal& Trainee::getFitnessGoal() const {
    return goal;
}

const std::vector<FoodEntry>& Trainee::getFoodDiary() const {
    return foodDiary;
}

const std::vector<ExerciseEntry>& Trainee::getExerciseDiary() const {
    return exerciseDiary;
}

const std::vector<unsigned>& Trainee::getFavoriteExercises() const {
    return favoriteExercises;
}

double Trainee::calculateBMI() const {
    double weightKg = getProfile().getWeight();

    double heightMeters = getProfile().getHeight() / HealthFormulas::CENTIMETERS_IN_METER;

    if (heightMeters <= Global::ZERO) {
        return Global::ZERO;
    }

    return weightKg / (heightMeters * heightMeters);
}

double Trainee::calculateBMR() const {
    if (!calculator) {
        return Global::ZERO;
    }

    return calculator->calculateBMR(getProfile());
}

double Trainee::calculateDailyCalorieTarget() const {
    double bmr = calculateBMR();

    ActivityLevel activity = getProfile().getActivityLevel();
    double tdee = bmr * HealthFormulas::ACTIVITY_MULTIPLIERS[static_cast<int>(activity)];

    GoalType goalType = goal.getType();
    double finalCalories = tdee + HealthFormulas::GOAL_CALORIE_MODIFIERS[static_cast<int>(goalType)];

    Gender gender = getProfile().getGender();
    double safeMinimum = HealthFormulas::MIN_SAFE_CALORIES[static_cast<int>(gender)];

    if (finalCalories < safeMinimum) {
        return safeMinimum;
    }

    return finalCalories;
}