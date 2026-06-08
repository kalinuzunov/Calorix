#include "FoodBuilder.h"
#include "../Constants.h"

using namespace Constants;

FoodBuilder::FoodBuilder(const std::string& name)
    : name(name),
      id(0),
      isExistingFood(false),
      caloriesPer100g(FoodLimits::DEFAULT_MACRO_VALUE),
      proteinPer100g(FoodLimits::DEFAULT_MACRO_VALUE),
      carbsPer100g(FoodLimits::DEFAULT_MACRO_VALUE),
      fatPer100g(FoodLimits::DEFAULT_MACRO_VALUE),
      fiberPer100g(FoodLimits::DEFAULT_MACRO_VALUE) {}

FoodBuilder& FoodBuilder::setId(unsigned id) {
    this->id = id;
    this->isExistingFood = true;
    return *this;
}

FoodBuilder& FoodBuilder::setCalories(double calories) {
    this->caloriesPer100g = calories;
    return *this;
}

FoodBuilder& FoodBuilder::setProtein(double protein) {
    this->proteinPer100g = protein;
    return *this;
}

FoodBuilder& FoodBuilder::setCarbs(double carbs) {
    this->carbsPer100g = carbs;
    return *this;
}

FoodBuilder& FoodBuilder::setFat(double fat) {
    this->fatPer100g = fat;
    return *this;
}

FoodBuilder& FoodBuilder::setFiber(double fiber) {
    this->fiberPer100g = fiber;
    return *this;
}

Food FoodBuilder::build() const {
    if (isExistingFood) {
        return Food(id, name, caloriesPer100g, proteinPer100g, carbsPer100g, fatPer100g, fiberPer100g);
    } else {
        return Food(name, caloriesPer100g, proteinPer100g, carbsPer100g, fatPer100g, fiberPer100g);
    }
}