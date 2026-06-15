#pragma once
#include "ICommand.h"
#include "../model/Enums.h"
#include <string>

class BlockUserCommand : public ICommand {
private:
    std::string targetUsername;

public:
    BlockUserCommand(const std::string& targetUsername);
    void execute(CalorixSystem& system) override;
};

class UnblockUserCommand : public ICommand {
    std::string targetUsername;
public:
    explicit UnblockUserCommand(const std::string& username);
    void execute(CalorixSystem& system) override;
};

class AddFoodCommand : public ICommand {
private:
    std::string name;
    double calories;
    double protein;
    double carbs;
    double fat;
    double fiber;

public:
    AddFoodCommand(const std::string& name, double calories, double protein, 
                   double carbs, double fat, double fiber);
    void execute(CalorixSystem& system) override;
};

class UpdateFoodCommand : public ICommand {
private:
    std::string foodName;
    double newCalories;

public:
    UpdateFoodCommand(const std::string& foodName, double newCalories);
    void execute(CalorixSystem& system) override;
};

class AddExerciseCommand : public ICommand {
private:
    std::string name;
    double caloriesBurnedPerHour;
    MuscleGroup muscleGroup;

public:
    AddExerciseCommand(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup);
    void execute(CalorixSystem& system) override;
};

class ListFoodsCommand : public ICommand {
public:
    void execute(CalorixSystem& system) override;
};

class ListExercisesCommand : public ICommand {
public:
    void execute(CalorixSystem& system) override;
};