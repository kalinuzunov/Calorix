#pragma once
#include "FileManager.h"
#include "../model/Exercise.h"
#include "../model/Enums.h"
#include <vector>
#include <string>

class ExerciseManager : public FileManager {
private:
    std::string filename;

    std::string muscleGroupToString(MuscleGroup group) const;
    MuscleGroup stringToMuscleGroup(const std::string& str) const;

public:
    ExerciseManager(const std::string& dbFilename);

    void saveExercise(const Exercise& exercise) const;
    std::vector<Exercise> loadAllExercises() const;
};