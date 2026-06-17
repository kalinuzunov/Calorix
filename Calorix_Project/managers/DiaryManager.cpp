#include "DiaryManager.h"
#include "../model/CalorixExceptions.h"
#include <fstream>
#include <sstream>
#include <iostream>

DiaryManager::DiaryManager(const std::string& foodFile, const std::string& exerciseFile)
    : foodLogsFile(foodFile), exerciseLogsFile(exerciseFile) {
}

void DiaryManager::saveFoodLog(const std::string& username, const FoodEntry& entry) const {
    std::ofstream file(foodLogsFile, std::ios::app);
    if (!file.is_open()) {
        throw InvalidCommandException("Could not open food logs file for writing.");
    }

    unsigned foodId = entry.getConsumable()->getId();
    file << username << " "
         << entry.getEntryId() << " "
         << foodId << " "
         << entry.getWeight() << " "
         << entry.getDate().toString() << "\n";
}

void DiaryManager::saveExerciseLog(const std::string& username, const ExerciseEntry& entry) const {
    std::ofstream file(exerciseLogsFile, std::ios::app);
    if (!file.is_open()) {
        throw InvalidCommandException("Could not open exercise logs file for writing.");
    }

    file << username << " "
         << entry.getEntryId() << " "
         << entry.getExerciseId() << " "
         << entry.getDurationMinutes() << " "
         << entry.getDate().toString() << "\n";
}

void DiaryManager::loadUserLogs(Trainee& trainee, 
                                const FoodManager& foodManager, 
                                const ExerciseManager& exerciseManager) const {
    std::string targetUser = trainee.getUsername();

    std::ifstream foodFile(foodLogsFile);
    if (foodFile.is_open()) {
        std::string line;
        while (std::getline(foodFile, line)) {
            if (line.empty()) continue;
            
            std::istringstream iss(line);
            std::string username;
            unsigned entryId, foodId;
            double weight;
            std::string dateStr;

            if (iss >> username >> entryId >> foodId >> weight >> dateStr) {
                if (username == targetUser) {
                    try {
                        auto consumable = foodManager.getFoodById(foodId); 
                        
                        Date date(dateStr);
                        FoodEntry entry(entryId, consumable, weight, date);
                        
                        trainee.logFood(entry); 
                        FoodEntry::updateNextId(entryId);
                    } catch (const std::exception& e) {
                        std::cerr << "[WARNING] Could not load food log for " << username << ": " << e.what() << "\n";
                    }
                }
            }
        }
    }

    std::ifstream exFile(exerciseLogsFile);
    if (exFile.is_open()) {
        std::string line;
        while (std::getline(exFile, line)) {
            if (line.empty()) continue;
            
            std::istringstream iss(line);
            std::string username;
            unsigned entryId, exerciseId;
            double duration;
            std::string dateStr;

            if (iss >> username >> entryId >> exerciseId >> duration >> dateStr) {
                if (username == targetUser) {
                    try {
                        Date date(dateStr);
                        ExerciseEntry entry(entryId, exerciseId, duration, date);
                        
                        trainee.logExercise(entry);
                        ExerciseEntry::updateNextId(entryId);
                    } catch (const std::exception& e) {
                        std::cerr << "[WARNING] Could not load exercise log for " << username << ": " << e.what() << "\n";
                    }
                }
            }
        }
    }
}