#pragma once
#include "FileManager.h"
#include "../model/User.h"
#include "../model/Enums.h"
#include "../model/FitnessGoal.h"
#include <vector>
#include <string>

class UserManager : public FileManager {
private:
    std::string filename;

    std::string genderToString(Gender gender) const;
    Gender stringToGender(const std::string& str) const;

    std::string activityToString(ActivityLevel level) const;
    ActivityLevel stringToActivity(const std::string& str) const;

    std::string goalTypeToString(GoalType type) const;
    GoalType stringToGoalType(const std::string& str) const;

public:
    UserManager(const std::string& dbFilename);

    void saveUser(const User& user) const;
    std::vector<User> loadAllUsers() const;

    void saveFitnessGoal(const std::string& username, const FitnessGoal& goal) const;
    bool loadFitnessGoal(const std::string& username, FitnessGoal& outGoal) const;
    void updateUserWeight(const std::string& username, double newWeight) const;
};