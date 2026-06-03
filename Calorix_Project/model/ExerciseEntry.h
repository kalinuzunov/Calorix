#pragma once
#include "Date.h"

class ExerciseEntry {
private:
    static unsigned nextId;
    unsigned entryId;
    unsigned exerciseId;
    double durationMinutes;
    Date date;

public:
    ExerciseEntry(unsigned exerciseId, double durationMinutes, const Date& date);

    ExerciseEntry(unsigned entryId, unsigned exerciseId, double durationMinutes, const Date& date);

    unsigned getEntryId() const;
    unsigned getExerciseId() const;
    double getDurationMinutes() const;
    Date getDate() const;

    static void updateNextId(unsigned loadedId);
};