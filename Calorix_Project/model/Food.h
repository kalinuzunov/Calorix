#pragma once
#include "IConsumable.h"

class Food : public IConsumable {
private:
    static unsigned nextId;
    unsigned id;
    std::string name;
    double caloriesPer100g;
    double proteinPer100g;
    double carbsPer100g;
    double fatPer100g;
    double fiberPer100g;

public:
    Food(const std::string& name, double calories, double protein, double carbs, double fat, double fiber);

    Food(unsigned id, const std::string& name, double calories, double protein, double carbs, double fat, double fiber);

    void setCalories(double newCalories);

    unsigned getId() const override;
    std::string getName() const override;
    double getCaloriesPer100g() const override;
    double getProteinPer100g() const override;
    double getCarbsPer100g() const override;
    double getFatPer100g() const override;
    double getFiberPer100g() const override;

    static void updateNextId(unsigned loadedId);
};