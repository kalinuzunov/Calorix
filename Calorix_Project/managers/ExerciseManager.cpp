#include "ExerciseManager.h"
#include "../Constants.h"
#include <iostream>
#include <stdexcept>

using namespace Constants;

ExerciseManager::ExerciseManager(const std::string& dbFilename) : filename(dbFilename) {}

std::string ExerciseManager::muscleGroupToString(MuscleGroup group) const {
    switch (group) {
        case MuscleGroup::CHEST: return "CHEST";
        case MuscleGroup::BACK: return "BACK";
        case MuscleGroup::LEGS: return "LEGS";
        case MuscleGroup::SHOULDERS: return "SHOULDERS";
        case MuscleGroup::ARMS: return "ARMS";
        case MuscleGroup::CORE: return "CORE";
        case MuscleGroup::CARDIO: return "CARDIO";
        default: return "UNKNOWN";
    }
}

MuscleGroup ExerciseManager::stringToMuscleGroup(const std::string& str) const {
    if (str == "CHEST") return MuscleGroup::CHEST;
    if (str == "BACK") return MuscleGroup::BACK;
    if (str == "LEGS") return MuscleGroup::LEGS;
    if (str == "SHOULDERS") return MuscleGroup::SHOULDERS;
    if (str == "ARMS") return MuscleGroup::ARMS;
    if (str == "CORE") return MuscleGroup::CORE;
    if (str == "CARDIO") return MuscleGroup::CARDIO;
    return MuscleGroup::UNKNOWN;
}

void ExerciseManager::saveExercise(const Exercise& exercise) const {
    std::string line = std::to_string(exercise.getExerciseId()) + Database::DELIMITER +
                       exercise.getName() + Database::DELIMITER +
                       std::to_string(exercise.getCaloriesBurnedPerHour()) + Database::DELIMITER +
                       muscleGroupToString(exercise.getMuscleGroup());

    appendLine(filename, line);
}

std::vector<Exercise> ExerciseManager::loadAllExercises() const {
    std::vector<Exercise> loadedExercises;
    std::vector<std::string> lines = readLines(filename);

    for (const auto& line : lines) {
        std::vector<std::string> data = split(line, Database::DELIMITER);

        if (data.size() == Database::EXERCISE_RECORD_FIELDS) { 
            try {
                unsigned id = std::stoul(data[0]);
                std::string name = data[1];
                double calories = std::stod(data[2]);
                MuscleGroup group = stringToMuscleGroup(data[3]);

                Exercise parsedExercise(id, name, calories, group);
                
                loadedExercises.push_back(parsedExercise);
                Exercise::updateNextId(id);

            } catch (const std::exception& e) {
                std::cerr << "[ERROR] Failed to parse exercise line: " << line << " -> " << e.what() << "\n";
            }
        } else {
            std::cerr << "[WARNING] Corrupted exercise record skipped: " << line << "\n";
        }
    }

    return loadedExercises;
}