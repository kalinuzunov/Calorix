#include "CalorixSystem.h"


CalorixSystem::CalorixSystem(const std::string& usersFile, const std::string& foodsFile, 
                             const std::string& recipesFile, const std::string& exercisesFile)
    : userManager(usersFile), foodManager(foodsFile), 
      recipeManager(recipesFile), exerciseManager(exercisesFile), 
      currentUser(nullptr) {
}