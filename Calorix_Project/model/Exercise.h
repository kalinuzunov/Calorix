#pragma once
#include <string>
#include "Enums.h"

class Exercise {
private:
    static unsigned nextId;
    unsigned exerciseId;
    std::string name;
    double caloriesBurnedPerHour;
    MuscleGroup muscleGroup;

public:

    Exercise(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup);
    Exercise(unsigned id, const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup);

    unsigned getExerciseId() const;
    const std::string& getName() const;
    double getCaloriesBurnedPerHour() const;
    MuscleGroup getMuscleGroup() const;

    static void updateNextId(unsigned loadedId);
};