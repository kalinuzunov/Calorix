#pragma once
#include "FileManager.h"
#include "../model/Recipe.h"
#include "../model/Food.h"
#include <vector>
#include <string>

class RecipeManager : public FileManager {
private:
    std::string filename;
public:
    RecipeManager(const std::string& dbFilename);

    void saveRecipe(const Recipe& recipe) const;

    std::vector<Recipe> loadAllRecipes(const std::vector<Food>& availableFoods) const;
};