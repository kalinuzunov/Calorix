#pragma once
#include "Date.h"

class FoodEntry {
private:
    static unsigned nextId;
    unsigned entryId;
    unsigned foodId;
    double quantityGrams;
    Date date;

public:
    FoodEntry(unsigned foodId, double quantityGrams, const Date& date);

    FoodEntry(unsigned entryId, unsigned foodId, double quantityGrams, const Date& date);

    unsigned getEntryId() const;
    unsigned getFoodId() const;
    double getQuantityGrams() const;
    Date getDate() const;

    static void updateNextId(unsigned loadedId);
};