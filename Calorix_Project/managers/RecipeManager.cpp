#include "RecipeManager.h"
#include "../Constants.h"
#include <iostream>
#include <algorithm>

using namespace Constants;

RecipeManager::RecipeManager(const std::string& dbFilename) : filename(dbFilename) {}

std::vector<std::string> RecipeManager::split(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start));

    return tokens;
}

void RecipeManager::saveRecipe(const Recipe& recipe) const {
    std::string line = std::to_string(recipe.getId()) + Database::DELIMITER + recipe.getName();

    auto ingredients = recipe.getIngredients();
    
    if (!ingredients.empty()) {
        line += Database::DELIMITER;
        for (size_t i = 0; i < ingredients.size(); ++i) {
            line += std::to_string(ingredients[i].first->getId()) + Database::RECIPE_WEIGHT_DELIMITER + 
                    std::to_string(ingredients[i].second);
            
            if (i < ingredients.size() - 1) {
                line += Database::RECIPE_INGR_DELIMITER;
            }
        }
    }

    appendLine(filename, line);
}

std::vector<Recipe> RecipeManager::loadAllRecipes(const std::vector<Food>& availableFoods) const {
    std::vector<Recipe> loadedRecipes;
    std::vector<std::string> lines = readLines(filename);

    for (const auto& line : lines) {
        std::vector<std::string> data = split(line, Database::DELIMITER);

        if (data.size() >= Database::RECIPE_MIN_FIELDS) {
            try {
                unsigned recipeId = std::stoul(data[0]);
                std::string recipeName = data[1];

                Recipe parsedRecipe(recipeId, recipeName);

                if (data.size() == Database::RECIPE_WITH_INGR_FIELDS) {
                    std::vector<std::string> ingredientsData = split(data[2], Database::RECIPE_INGR_DELIMITER);
                    
                    for (const auto& ingrStr : ingredientsData) {
                        std::vector<std::string> pairData = split(ingrStr, Database::RECIPE_WEIGHT_DELIMITER);
                        
                        if (pairData.size() == Database::INGREDIENT_PAIR_FIELDS) {
                            unsigned foodId = std::stoul(pairData[0]);
                            double weight = std::stod(pairData[1]);

                            auto it = std::find_if(availableFoods.begin(), availableFoods.end(),
                                [foodId](const Food& f) { return f.getId() == foodId; });

                            if (it != availableFoods.end()) {
                                parsedRecipe.addIngredient(std::make_shared<Food>(*it), weight);
                            } else {
                                std::cerr << "[WARNING] Ingredient with ID " << foodId 
                                          << " not found for Recipe '" << recipeName << "'. Skipping ingredient.\n";
                            }
                        } else {
                            std::cerr << "[WARNING] Corrupted ingredient pair in recipe '" << recipeName << "': " << ingrStr << "\n";
                        }
                    }
                }

                loadedRecipes.push_back(parsedRecipe);
                Recipe::updateNextId(recipeId);

            } catch (const std::exception& e) {
                std::cerr << "[ERROR] Failed to parse recipe: " << line << " -> " << e.what() << "\n";
            }
        } else {
            std::cerr << "[WARNING] Corrupted recipe record skipped: " << line << "\n";
        }
    }

    return loadedRecipes;
}