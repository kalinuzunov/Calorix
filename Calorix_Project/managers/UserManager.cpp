#include "UserManager.h"
#include "../Constants.h"
#include <iostream>
#include <stdexcept>

#include "UserProfileBuilder.h"

using namespace Constants;

UserManager::UserManager(const std::string& dbFilename) : filename(dbFilename) {}

std::vector<std::string> UserManager::split(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start));

    return tokens;
}

std::string UserManager::genderToString(Gender gender) const {
    switch (gender) {
        case Gender::MALE: return "MALE";
        case Gender::FEMALE: return "FEMALE";
        default: return "OTHER";
    }
}

Gender UserManager::stringToGender(const std::string& str) const {
    if (str == "MALE") return Gender::MALE;
    if (str == "FEMALE") return Gender::FEMALE;
    return Gender::OTHER;
}

std::string UserManager::activityToString(ActivityLevel level) const {
    switch (level) {
        case ActivityLevel::SEDENTARY: return "SEDENTARY";
        case ActivityLevel::LIGHT: return "LIGHT";
        case ActivityLevel::MODERATE: return "MODERATE";
        case ActivityLevel::ACTIVE: return "ACTIVE";
        case ActivityLevel::VERY_ACTIVE: return "VERY_ACTIVE";
        default: return "SEDENTARY";
    }
}

ActivityLevel UserManager::stringToActivity(const std::string& str) const {
    if (str == "LIGHT") return ActivityLevel::LIGHT;
    if (str == "MODERATE") return ActivityLevel::MODERATE;
    if (str == "ACTIVE") return ActivityLevel::ACTIVE;
    if (str == "VERY_ACTIVE") return ActivityLevel::VERY_ACTIVE;
    return ActivityLevel::SEDENTARY;
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

                UserProfileBuilder builder;
                UserProfile profile = builder.setWeight(weight)
                                             .setHeight(height)
                                             .setAge(age)
                                             .setGender(gender)
                                             .setActivityLevel(activity)
                                             .build();

                Password userPassword(passwordStr);
                User parsedUser(id, username, userPassword, profile);
                
                loadedUsers.push_back(parsedUser);
                User::updateNextId(id);

            } catch (const std::exception& e) {
                std::cerr << "[ERROR] Failed to parse user line: " << line << " -> " << e.what() << "\n";
            }
        } else {
            std::cerr << "[WARNING] Corrupted user record skipped: " << line << "\n";
        }
    }

    return loadedUsers;
}