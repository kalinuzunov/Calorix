#pragma once
#include <string>

class Food {
private:
    static unsigned nextId;
    unsigned foodId;
    double caloriesPer100g;
    double proteinPer100g;
    double carbsPer100g;
    double fatPer100g;
    double fiberPer100g;
    std::string name;

public:
    Food(const std::string& name, double calories, double protein, double carbs, double fat, double fiber);

    Food(unsigned id, const std::string& name, double calories, double protein, double carbs, double fat, double fiber);

    unsigned getFoodId() const;
    const std::string& getName() const;

    double getCaloriesPer100g() const;
    double getProteinPer100g() const;
    double getCarbsPer100g() const;
    double getFatPer100g() const;
    double getFiberPer100g() const;

    static void updateNextId(unsigned loadedId);
};