#include "FoodEntry.h"
#include "../Constants.h"
#include "CalorixExceptions.h"

using namespace Constants;

unsigned FoodEntry::nextId = Global::STARTING_ID;

FoodEntry::FoodEntry(std::shared_ptr<IConsumable> item, double weightGrams, const Date& date)
    : entryId(nextId++), consumableItem(item), weightGrams(weightGrams), date(date) {

    if (!this->consumableItem) {
        throw InvalidNameException("Food entry must contain a valid food or recipe.");
    }

    if (this->weightGrams <= Global::ZERO) {
        throw InvalidMacroException("Consumed weight must be greater than zero.");
    }
}

FoodEntry::FoodEntry(unsigned entryId, std::shared_ptr<IConsumable> item, double weightGrams, const Date& date)
    : entryId(entryId), consumableItem(item), weightGrams(weightGrams), date(date) {

    if (!this->consumableItem) {
        throw InvalidNameException("Food entry must contain a valid food or recipe.");
    }

    if (this->weightGrams <= Global::ZERO) {
        throw InvalidMacroException("Consumed weight must be greater than zero.");
    }
}

unsigned FoodEntry::getEntryId() const {
    return entryId;
}

std::shared_ptr<IConsumable> FoodEntry::getItem() const {
    return consumableItem;
}

double FoodEntry::getWeight() const {
    return weightGrams;
}

Date FoodEntry::getDate() const {
    return date;
}

double FoodEntry::getTotalCalories() const {
    return (consumableItem->getCaloriesPer100g() / FoodLimits::BASE_GRAMS_UNIT) * weightGrams;
}

double FoodEntry::getTotalProtein() const {
    return (consumableItem->getProteinPer100g() / FoodLimits::BASE_GRAMS_UNIT) * weightGrams;
}

double FoodEntry::getTotalCarbs() const {
    return (consumableItem->getCarbsPer100g() / FoodLimits::BASE_GRAMS_UNIT) * weightGrams;
}

double FoodEntry::getTotalFat() const {
    return (consumableItem->getFatPer100g() / FoodLimits::BASE_GRAMS_UNIT) * weightGrams;
}

double FoodEntry::getTotalFiber() const {
    return (consumableItem->getFiberPer100g() / FoodLimits::BASE_GRAMS_UNIT) * weightGrams;
}

std::shared_ptr<IConsumable> FoodEntry::getConsumable() const {
    return consumableItem;
}

void FoodEntry::updateNextId(unsigned loadedId) {
    if (loadedId >= nextId) {
        nextId = loadedId + 1;
    }
}