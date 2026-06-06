#pragma once
#include "IConsumable.h"
#include <vector>
#include <memory>
#include <functional>

class Recipe : public IConsumable {
private:
    static unsigned nextId;
    unsigned id;
    std::string name;

    std::vector<std::pair<std::shared_ptr<IConsumable>, double>> ingredients;

    double calculateMacro(const std::function<double(const IConsumable*)>& extractor) const;

public:
    Recipe(const std::string& name);
    Recipe(unsigned id, const std::string& name);

    void addIngredient(std::shared_ptr<IConsumable> ingredient, double weightGrams);
    double getTotalWeight() const;

    unsigned getId() const override;
    std::string getName() const override;

    double getCaloriesPer100g() const override;
    double getProteinPer100g() const override;
    double getCarbsPer100g() const override;
    double getFatPer100g() const override;
    double getFiberPer100g() const override;

    static void updateNextId(unsigned loadedId);
};