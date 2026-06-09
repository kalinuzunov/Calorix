#pragma once
#include "FileManager.h"
#include "../model/User.h"
#include "../model/Enums.h"
#include <vector>
#include <string>

class UserManager : public FileManager {
private:
    std::string filename;

    std::vector<std::string> split(const std::string& str, char delimiter) const;

    std::string genderToString(Gender gender) const;
    Gender stringToGender(const std::string& str) const;

    std::string activityToString(ActivityLevel level) const;
    ActivityLevel stringToActivity(const std::string& str) const;

public:
    UserManager(const std::string& dbFilename);

    void saveUser(const User& user) const;
    std::vector<User> loadAllUsers() const;
};