#pragma once
#include "FileManager.h"
#include "FoodManager.h"
#include "ExerciseManager.h"
#include "../model/Trainee.h"
#include "../model/FoodEntry.h"
#include "../model/ExerciseEntry.h"
#include <string>
#include <vector>
#include <memory>

class DiaryManager : public FileManager {
private:
    std::string foodLogsFile;
    std::string exerciseLogsFile;

public:
    DiaryManager(const std::string& foodFile, const std::string& exerciseFile);

    void saveFoodLog(const std::string& username, const FoodEntry& entry) const;
    void saveExerciseLog(const std::string& username, const ExerciseEntry& entry) const;

    void loadUserLogs(Trainee& trainee, 
                      const FoodManager& foodManager, 
                      const ExerciseManager& exerciseManager) const;
};