#include "Exercise.h"
#include "Constants.h"
#include "CalorixExceptions.h"

using namespace Constants;

unsigned Exercise::nextId = Global::STARTING_ID;

Exercise::Exercise(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup)
    : exerciseId(nextId++),
      name(name),
      caloriesBurnedPerHour(caloriesBurnedPerHour),
      muscleGroup(muscleGroup) {

    if (this->name.empty() || this->name == Global::EMPTY_STRING) {
        throw InvalidNameException("Exercise name cannot be empty.");
    }
    if (this->caloriesBurnedPerHour < ExerciseLimits::DEFAULT_CALORIES_VALUE) {
        throw InvalidMacroException("Calories burned per hour cannot be negative.");
    }
}

Exercise::Exercise(unsigned id, const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup)
    : exerciseId(id),name(name),
      caloriesBurnedPerHour(caloriesBurnedPerHour),muscleGroup(muscleGroup) {

    if (this->name.empty() || this->name == Global::EMPTY_STRING) {
        throw InvalidNameException("Exercise name cannot be empty.");
    }
    if (this->caloriesBurnedPerHour < ExerciseLimits::DEFAULT_CALORIES_VALUE) {
        throw InvalidMacroException("Calories burned per hour cannot be negative.");
    }
}

void Exercise::updateNextId(unsigned loadedId) {
    if (loadedId >= nextId) {
        nextId = loadedId + 1;
    }
}

unsigned Exercise::getExerciseId() const {
    return exerciseId;
}
const std::string& Exercise::getName() const {
    return name;
}
double Exercise::getCaloriesBurnedPerHour() const {
    return caloriesBurnedPerHour;
}
MuscleGroup Exercise::getMuscleGroup() const {
    return muscleGroup;
}