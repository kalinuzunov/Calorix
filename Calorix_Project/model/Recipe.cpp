#include "Recipe.h"
#include "../Constants.h"
#include "CalorixExceptions.h"

using namespace Constants;

unsigned Recipe::nextId = Global::STARTING_ID;

Recipe::Recipe(const std::string& name) : id(nextId++), name(name) {
    if (this->name.empty() || this->name == Global::EMPTY_STRING) {
        throw InvalidNameException("Recipe name cannot be empty.");
    }
}

Recipe::Recipe(unsigned id, const std::string& name) : id(id), name(name) {
    if (this->name.empty() || this->name == Global::EMPTY_STRING) {
        throw InvalidNameException("Recipe name cannot be empty.");
    }
}

void Recipe::addIngredient(std::shared_ptr<IConsumable> ingredient, double weightGrams) {
    if (ingredient && weightGrams > Global::ZERO) {
        ingredients.push_back({ingredient, weightGrams});
    }
}

double Recipe::getTotalWeight() const {
    double total = Global::ZERO;
    for (const auto& item : ingredients) {
        total += item.second;
    }
    return total;
}

unsigned Recipe::getId() const { return id; }

std::string Recipe::getName() const { return name; }

double Recipe::calculateMacro(const std::function<double(const IConsumable*)>& extractor) const {
    double totalWeight = getTotalWeight();
    if (totalWeight <= Global::ZERO) return Global::ZERO;

    double totalMacro = Global::ZERO;
    for (const auto& item : ingredients) {
        totalMacro += (extractor(item.first.get()) / FoodLimits::BASE_GRAMS_UNIT) * item.second;
    }

    return (totalMacro / totalWeight) * FoodLimits::BASE_GRAMS_UNIT;
}

double Recipe::getCaloriesPer100g() const {
    return calculateMacro([](const IConsumable* item) { return item->getCaloriesPer100g(); });
}

double Recipe::getProteinPer100g() const {
    return calculateMacro([](const IConsumable* item) { return item->getProteinPer100g(); });
}

double Recipe::getCarbsPer100g() const {
    return calculateMacro([](const IConsumable* item) { return item->getCarbsPer100g(); });
}

double Recipe::getFatPer100g() const {
    return calculateMacro([](const IConsumable* item) { return item->getFatPer100g(); });
}

double Recipe::getFiberPer100g() const {
    return calculateMacro([](const IConsumable* item) { return item->getFiberPer100g(); });
}

void Recipe::updateNextId(unsigned loadedId) {
    if (loadedId >= nextId) {
        nextId = loadedId + 1;
    }
}