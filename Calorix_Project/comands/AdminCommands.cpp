#include "AdminCommands.h"
#include "../CalorixSystem.h"

BlockUserCommand::BlockUserCommand(const std::string& targetUsername)
    : targetUsername(targetUsername) {}

void BlockUserCommand::execute(CalorixSystem& system) {
    system.blockUser(targetUsername);
}


AddFoodCommand::AddFoodCommand(const std::string& name, double calories, double protein, 
                               double carbs, double fat, double fiber)
    : name(name), calories(calories), protein(protein), carbs(carbs), fat(fat), fiber(fiber) {}

void AddFoodCommand::execute(CalorixSystem& system) {
    system.addFood(name, calories, protein, carbs, fat, fiber);
}


UpdateFoodCommand::UpdateFoodCommand(const std::string& foodName, double newCalories)
    : foodName(foodName), newCalories(newCalories) {}

void UpdateFoodCommand::execute(CalorixSystem& system) {
    system.updateFood(foodName, newCalories);
}


AddExerciseCommand::AddExerciseCommand(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup)
    : name(name), caloriesBurnedPerHour(caloriesBurnedPerHour), muscleGroup(muscleGroup) {}

void AddExerciseCommand::execute(CalorixSystem& system) {
    system.addExercise(name, caloriesBurnedPerHour, muscleGroup);
}