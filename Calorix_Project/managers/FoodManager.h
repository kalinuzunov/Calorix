#pragma once
#include "FileManager.h"
#include "../model/Food.h"
#include <vector>
#include <string>
#include <memory>

class FoodManager : public FileManager {
private:
    std::string filename;

public:
    FoodManager(const std::string& dbFilename);

    std::vector<Food> loadAllFoods() const;

    std::shared_ptr<Food> getFoodById(unsigned id) const;

    void saveFood(Food& food) const;

    void updateFoodCalories(const std::string& foodName, double newCalories);
};