#include "Food.h"
#include "../Constants.h"
#include "CalorixExceptions.h"

unsigned Food::nextId = Constants::Global::STARTING_ID;
using namespace Constants;

Food::Food(const std::string& name, double calories, double protein, double carbs, double fat, double fiber)
    : id(nextId++), name(name),
      caloriesPer100g(calories), proteinPer100g(protein),
      carbsPer100g(carbs), fatPer100g(fat), fiberPer100g(fiber) {

    if (this->name.empty() || this->name == Global::EMPTY_STRING) {
        throw InvalidNameException("Food name cannot be empty.");
    }

    if (this->caloriesPer100g < FoodLimits::DEFAULT_MACRO_VALUE ||
        this->proteinPer100g < FoodLimits::DEFAULT_MACRO_VALUE ||
        this->carbsPer100g < FoodLimits::DEFAULT_MACRO_VALUE ||
        this->fatPer100g < FoodLimits::DEFAULT_MACRO_VALUE ||
        this->fiberPer100g < FoodLimits::DEFAULT_MACRO_VALUE) {
        throw InvalidMacroException("Food macronutrients and calories cannot be negative.");
        }
}

Food::Food(unsigned id, const std::string& name, double calories, double protein, double carbs, double fat, double fiber)
    : id(id), name(name),
      caloriesPer100g(calories), proteinPer100g(protein),
      carbsPer100g(carbs), fatPer100g(fat), fiberPer100g(fiber) {

    if (this->name.empty() || this->name == Global::EMPTY_STRING) {
        throw InvalidNameException("Food name cannot be empty.");
    }

    if (this->caloriesPer100g < FoodLimits::DEFAULT_MACRO_VALUE ||
        this->proteinPer100g < FoodLimits::DEFAULT_MACRO_VALUE ||
        this->carbsPer100g < FoodLimits::DEFAULT_MACRO_VALUE ||
        this->fatPer100g < FoodLimits::DEFAULT_MACRO_VALUE ||
        this->fiberPer100g < FoodLimits::DEFAULT_MACRO_VALUE) {
        throw InvalidMacroException("Food macronutrients and calories cannot be negative.");
        }
}

void Food::setCalories(double newCalories) {
    if (newCalories < Constants::Global::ZERO) {
        throw InvalidMacroException("Calories cannot be negative!");
    }
    caloriesPer100g = newCalories;
}

unsigned Food::getId() const {
    return id;
}
std::string Food::getName() const {
    return name;
}
double Food::getCaloriesPer100g() const {
    return caloriesPer100g;
}
double Food::getProteinPer100g() const {
    return proteinPer100g;
}
double Food::getCarbsPer100g() const {
    return carbsPer100g;
}
double Food::getFatPer100g() const {
    return fatPer100g;
}
double Food::getFiberPer100g() const {
    return fiberPer100g;
}

void Food::updateNextId(unsigned loadedId) {
    if (loadedId >= nextId) {
        nextId = loadedId + 1;
    }
}