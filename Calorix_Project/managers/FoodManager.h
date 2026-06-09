#pragma once
#include "FileManager.h"
#include "../model/Food.h"
#include <vector>
#include <string>

class FoodManager : public FileManager {
private:
    std::string filename;

public:
    FoodManager(const std::string& dbFilename);

    std::vector<Food> loadAllFoods() const;

    void saveFood(const Food& food) const;
};