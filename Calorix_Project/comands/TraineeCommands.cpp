#include "TraineeCommands.h"
#include "../CalorixSystem.h"

SetGoalCommand::SetGoalCommand(GoalType goalType, double targetValue, const Date& deadline)
    : goalType(goalType), targetValue(targetValue), deadline(deadline) {}

void SetGoalCommand::execute(CalorixSystem& system) {
    system.setGoal(goalType, targetValue, deadline);
}


LogFoodCommand::LogFoodCommand(const std::string& foodName, double quantityGrams)
    : foodName(foodName), quantityGrams(quantityGrams) {}

void LogFoodCommand::execute(CalorixSystem& system) {
    system.logFood(foodName, quantityGrams);
}

LogExerciseCommand::LogExerciseCommand(const std::string& exerciseName, int durationMinutes)
    : exerciseName(exerciseName), durationMinutes(durationMinutes) {}

void LogExerciseCommand::execute(CalorixSystem& system) {
    system.logExercise(exerciseName, durationMinutes);
}


void ViewDailySummaryCommand::execute(CalorixSystem& system) {
    system.viewDailySummary();
}

void ViewProgressCommand::execute(CalorixSystem& system) {
    system.viewProgress();
}


void CalculateBMICommand::execute(CalorixSystem& system) {
    system.calculateBMI();
}


void CalculateBMRCommand::execute(CalorixSystem& system) {
    system.calculateBMR();
}


GenerateWorkoutPlanCommand::GenerateWorkoutPlanCommand(int durationMinutes)
    : durationMinutes(durationMinutes) {}

void GenerateWorkoutPlanCommand::execute(CalorixSystem& system) {
    system.generateWorkoutPlan(durationMinutes);
}


AddToFavoritesCommand::AddToFavoritesCommand(const std::string& exerciseName)
    : exerciseName(exerciseName) {}

void AddToFavoritesCommand::execute(CalorixSystem& system) {
    system.addToFavorites(exerciseName);
}

void ViewFavoritesCommand::execute(CalorixSystem& system) {
    system.viewFavorites();
}

UpdateWeightCommand::UpdateWeightCommand(double newWeight) : newWeight(newWeight) {}

void UpdateWeightCommand::execute(CalorixSystem& system) {
    system.updateWeight(newWeight);
}