#pragma once
#include "ICommand.h"
#include "../model/Enums.h"
#include "../model/Date.h"
#include <string>

class SetGoalCommand : public ICommand {
private:
    GoalType goalType;
    double targetValue;
    Date deadline;

public:
    SetGoalCommand(GoalType goalType, double targetValue, const Date& deadline);
    void execute(CalorixSystem& system) override;
};

class LogFoodCommand : public ICommand {
private:
    std::string foodName;
    double quantityGrams;

public:
    LogFoodCommand(const std::string& foodName, double quantityGrams);
    void execute(CalorixSystem& system) override;
};

class LogExerciseCommand : public ICommand {
private:
    std::string exerciseName;
    int durationMinutes;

public:
    LogExerciseCommand(const std::string& exerciseName, int durationMinutes);
    void execute(CalorixSystem& system) override;
};

class ViewDailySummaryCommand : public ICommand {
public:
    ViewDailySummaryCommand() = default;
    void execute(CalorixSystem& system) override;
};

class ViewProgressCommand : public ICommand {
public:
    ViewProgressCommand() = default;
    void execute(CalorixSystem& system) override;
};

class CalculateBMICommand : public ICommand {
public:
    CalculateBMICommand() = default;
    void execute(CalorixSystem& system) override;
};

class CalculateBMRCommand : public ICommand {
public:
    CalculateBMRCommand() = default;
    void execute(CalorixSystem& system) override;
};

class GenerateWorkoutPlanCommand : public ICommand {
private:
    int durationMinutes;

public:
    GenerateWorkoutPlanCommand(int durationMinutes);
    void execute(CalorixSystem& system) override;
};

class AddToFavoritesCommand : public ICommand {
private:
    std::string exerciseName;

public:
    AddToFavoritesCommand(const std::string& exerciseName);
    void execute(CalorixSystem& system) override;
};

class ViewFavoritesCommand : public ICommand {
public:
    ViewFavoritesCommand() = default;
    void execute(CalorixSystem& system) override;
};

class UpdateWeightCommand : public ICommand {
private:
    double newWeight;

public:
    explicit UpdateWeightCommand(double newWeight);
    void execute(CalorixSystem& system) override;
};