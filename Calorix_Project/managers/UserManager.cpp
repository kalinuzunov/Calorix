#include "UserManager.h"
#include "../Constants.h"
#include <iostream>
#include <fstream>
#include "UserProfileBuilder.h"

using namespace Constants;

UserManager::UserManager(const std::string& dbFilename) : filename(dbFilename) {}

std::string UserManager::genderToString(Gender gender) const {
    if (gender == Gender::MALE) return "MALE";
    if (gender == Gender::FEMALE) return "FEMALE";
    return "OTHER";
}

Gender UserManager::stringToGender(const std::string& str) const {
    if (str == "MALE") return Gender::MALE;
    if (str == "FEMALE") return Gender::FEMALE;
    return Gender::OTHER;
}

std::string UserManager::activityToString(ActivityLevel level) const {
    if (level == ActivityLevel::LIGHT) return "LIGHT";
    if (level == ActivityLevel::MODERATE) return "MODERATE";
    if (level == ActivityLevel::ACTIVE) return "ACTIVE";
    if (level == ActivityLevel::VERY_ACTIVE) return "VERY_ACTIVE";
    return "SEDENTARY";
}

ActivityLevel UserManager::stringToActivity(const std::string& str) const {
    if (str == "LIGHT") return ActivityLevel::LIGHT;
    if (str == "MODERATE") return ActivityLevel::MODERATE;
    if (str == "ACTIVE") return ActivityLevel::ACTIVE;
    if (str == "VERY_ACTIVE") return ActivityLevel::VERY_ACTIVE;
    return ActivityLevel::SEDENTARY;
}

std::string UserManager::goalTypeToString(GoalType type) const {
    if (type == GoalType::WEIGHT_LOSS) return "WEIGHT_LOSS";
    if (type == GoalType::BULKING) return "BULKING";
    if (type == GoalType::MAINTENANCE) return "MAINTENANCE";
    return "NONE";
}

GoalType UserManager::stringToGoalType(const std::string& str) const {
    if (str == "WEIGHT_LOSS") return GoalType::WEIGHT_LOSS;
    if (str == "BULKING") return GoalType::BULKING;
    if (str == "MAINTENANCE") return GoalType::MAINTENANCE;
    return GoalType::NONE;
}

void UserManager::saveUser(const User& user) const {
    const UserProfile& profile = user.getProfile();
    std::string line = std::to_string(user.getUserId()) + Database::DELIMITER +
                       user.getUsername() + Database::DELIMITER +
                       user.getPassword() + Database::DELIMITER +
                       std::to_string(profile.getWeight()) + Database::DELIMITER +
                       std::to_string(profile.getHeight()) + Database::DELIMITER +
                       std::to_string(profile.getAge()) + Database::DELIMITER +
                       genderToString(profile.getGender()) + Database::DELIMITER +
                       activityToString(profile.getActivityLevel());
    appendLine(filename, line);
}

std::vector<User> UserManager::loadAllUsers() const {
    std::vector<User> loadedUsers;
    std::vector<std::string> lines = readLines(filename);
    for (const auto& line : lines) {
        std::vector<std::string> data = split(line, Database::DELIMITER);
        if (data.size() == Database::USER_RECORD_FIELDS) {
            try {
                unsigned id = std::stoul(data[0]);
                std::string username = data[1];
                std::string passwordStr = data[2];
                double weight = std::stod(data[3]);
                double height = std::stod(data[4]);
                unsigned age = std::stoul(data[5]);
                Gender gender = stringToGender(data[6]);
                ActivityLevel activity = stringToActivity(data[7]);

                UserProfile profile = UserProfileBuilder().setWeight(weight).setHeight(height).setAge(age).setGender(gender).setActivityLevel(activity).build();
                User parsedUser(id, username, Password(passwordStr), profile);
                loadedUsers.push_back(parsedUser);
                User::updateNextId(id);
            } catch (...) {}
        }
    }
    return loadedUsers;
}

void UserManager::saveFitnessGoal(const std::string& username, const FitnessGoal& goal) const {
    std::string line = username + Database::DELIMITER +
                       goalTypeToString(goal.getType()) + Database::DELIMITER +
                       std::to_string(goal.getTargetValue()) + Database::DELIMITER +
                       goal.getStartDate().toString() + Database::DELIMITER +
                       goal.getDeadline().toString();
    appendLine("goals.txt", line);
}

bool UserManager::loadFitnessGoal(const std::string& username, FitnessGoal& outGoal) const {
    std::vector<std::string> lines = readLines("goals.txt");
    bool found = false;

    for (const auto& line : lines) {
        std::vector<std::string> data = split(line, Database::DELIMITER);
        if (data.size() == Constants::Database::GOAL_RECORD_FIELDS && data[0] == username) {
            try {
                GoalType type = stringToGoalType(data[1]);
                double target = std::stod(data[2]);
                Date start(data[3]);
                Date deadline(data[4]);
                outGoal = FitnessGoal(type, target, start, deadline);
                found = true;
            } catch (...) {}
        }
    }
    return found;
}

void UserManager::updateUserWeight(const std::string& username, double newWeight) const {
    std::vector<std::string> lines = readLines(filename);
    std::ofstream file(filename);
    for (const auto& line : lines) {
        std::vector<std::string> data = split(line, Database::DELIMITER);
        if (data.size() == Database::USER_RECORD_FIELDS && data[1] == username) {
            data[3] = std::to_string(newWeight);
            std::string newLine = data[0];
            for (size_t i = 1; i < data.size(); ++i) {
                newLine += Database::DELIMITER + data[i];
            }
            file << newLine << "\n";
        } else {
            file << line << "\n";
        }
    }
}