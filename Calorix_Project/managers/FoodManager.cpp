#include "FoodManager.h"
#include "../model/FoodBuilder.h"
#include "../Constants.h"
#include <iostream>
#include <stdexcept>

using namespace Constants;

FoodManager::FoodManager(const std::string& dbFilename) : filename(dbFilename) {}

void FoodManager::saveFood(const Food& food) const {
    std::string line = std::to_string(food.getId()) + Database::DELIMITER +
                       food.getName() + Database::DELIMITER +
                       std::to_string(food.getCaloriesPer100g()) + Database::DELIMITER +
                       std::to_string(food.getProteinPer100g()) + Database::DELIMITER +
                       std::to_string(food.getCarbsPer100g()) + Database::DELIMITER +
                       std::to_string(food.getFatPer100g()) + Database::DELIMITER +
                       std::to_string(food.getFiberPer100g());

    appendLine(filename, line);
}

std::vector<Food> FoodManager::loadAllFoods() const {
    std::vector<Food> loadedFoods;
    std::vector<std::string> lines = readLines(filename);

    for (const auto& line : lines) {
        std::vector<std::string> data = split(line, Database::DELIMITER);

        if (data.size() == Database::FOOD_RECORD_FIELDS) {
            try {
                unsigned id = std::stoul(data[0]);
                std::string name = data[1];
                double calories = std::stod(data[2]);
                double protein = std::stod(data[3]);
                double carbs = std::stod(data[4]);
                double fat = std::stod(data[5]);
                double fiber = std::stod(data[6]);

                FoodBuilder builder(name);
                Food parsedFood = builder.setId(id)
                                         .setCalories(calories)
                                         .setProtein(protein)
                                         .setCarbs(carbs)
                                         .setFat(fat)
                                         .setFiber(fiber)
                                         .build();

                loadedFoods.push_back(parsedFood);
                Food::updateNextId(id);

            } catch (const std::exception& e) {
                std::cerr << "[ERROR] Data conversion failed for line: " << line << " -> " << e.what() << "\n";
            }
        } else {
            std::cerr << "[WARNING] Database corruption detected in foods file. Skipping line: " << line << "\n";
        }
    }

    return loadedFoods;
}