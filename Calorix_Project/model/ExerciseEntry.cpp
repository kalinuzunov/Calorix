#include "ExerciseEntry.h"
#include "../Constants.h"
#include <stdexcept>

using namespace Constants;

unsigned ExerciseEntry::nextId = Global::STARTING_ID;

ExerciseEntry::ExerciseEntry(unsigned exerciseId, double durationMinutes, const Date& date)
    : entryId(nextId++), 
      exerciseId(exerciseId), 
      durationMinutes(durationMinutes), 
      date(date) {

    if (this->durationMinutes <= ExerciseLimits::DEFAULT_DURATION_VALUE) {
        throw std::invalid_argument("Duration in minutes must be strictly positive.");
    }
}

ExerciseEntry::ExerciseEntry(unsigned entryId, unsigned exerciseId, double durationMinutes, const Date& date)
    : entryId(entryId), 
      exerciseId(exerciseId), 
      durationMinutes(durationMinutes), 
      date(date) {
      
    // Същата валидация
    if (this->durationMinutes <= ExerciseLimits::DEFAULT_DURATION_VALUE) {
        throw std::invalid_argument("Duration in minutes must be strictly positive.");
    }
}

void ExerciseEntry::updateNextId(unsigned loadedId) {
    if (loadedId >= nextId) {
        nextId = loadedId + 1;
    }
}

unsigned ExerciseEntry::getEntryId() const { return entryId; }
unsigned ExerciseEntry::getExerciseId() const { return exerciseId; }
double ExerciseEntry::getDurationMinutes() const { return durationMinutes; }
Date ExerciseEntry::getDate() const { return date; }