#include "Food.h"
#include "../Constants.h"

using namespace Constants;

unsigned Food::nextId = 1;

Food::Food()
    : foodId(0),caloriesPer100g(FoodLimits::DEFAULT_MACRO_VALUE),
      proteinPer100g(FoodLimits::DEFAULT_MACRO_VALUE), carbsPer100g(FoodLimits::DEFAULT_MACRO_VALUE),
      fatPer100g(FoodLimits::DEFAULT_MACRO_VALUE), fiberPer100g(FoodLimits::DEFAULT_MACRO_VALUE),
      name(Global::EMPTY_STRING) {}

Food::Food(const std::string& name, double calories, double protein, double carbs, double fat, double fiber)
    : foodId(nextId++),caloriesPer100g(calories), proteinPer100g(protein),
      carbsPer100g(carbs), fatPer100g(fat), fiberPer100g(fiber),name(name) {}

unsigned Food::getFoodId() const {
    return foodId;
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