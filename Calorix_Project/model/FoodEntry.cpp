#include "FoodEntry.h"
#include "../Constants.h"
#include "CalorixExceptions.h"

using namespace Constants;

unsigned FoodEntry::nextId = Global::STARTING_ID;

FoodEntry::FoodEntry(unsigned foodId, double quantityGrams, const Date& date)
    : entryId(nextId++), foodId(foodId),
      quantityGrams(quantityGrams), date(date) {

    if (this->quantityGrams <= FoodLimits::DEFAULT_MACRO_VALUE) {
        throw InvalidWeightException("Quantity in grams must be strictly positive.");
    }
}

FoodEntry::FoodEntry(unsigned entryId, unsigned foodId, double quantityGrams, const Date& date)
    : entryId(entryId), foodId(foodId),
      quantityGrams(quantityGrams), date(date) {

    if (this->quantityGrams <= FoodLimits::DEFAULT_MACRO_VALUE) {
        throw InvalidWeightException("Quantity in grams must be strictly positive.");
    }
}

void FoodEntry::updateNextId(unsigned loadedId) {
    if (loadedId >= nextId) {
        nextId = loadedId + 1;
    }
}

unsigned FoodEntry::getEntryId() const {
    return entryId;
}
unsigned FoodEntry::getFoodId() const {
    return foodId;
}
double FoodEntry::getQuantityGrams() const {
    return quantityGrams;
}
Date FoodEntry::getDate() const {
    return date;
}