#pragma once
#include "Food.h"
#include <string>

class FoodBuilder {
private:
    std::string name;
    double caloriesPer100g;
    double proteinPer100g;
    double carbsPer100g;
    double fatPer100g;
    double fiberPer100g;

public:
    FoodBuilder(const std::string& name);

    FoodBuilder& setCalories(double calories);
    FoodBuilder& setProtein(double protein);
    FoodBuilder& setCarbs(double carbs);
    FoodBuilder& setFat(double fat);
    FoodBuilder& setFiber(double fiber);

    Food build() const;
};