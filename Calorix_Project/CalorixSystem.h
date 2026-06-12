#pragma once

#include <memory>
#include <string>

#include "managers/UserManager.h"
#include "managers/FoodManager.h"
#include "managers/RecipeManager.h"
#include "managers/ExerciseManager.h"

#include "model/User.h"
#include "model/Enums.h"

class CalorixSystem {
private:
    UserManager userManager;
    FoodManager foodManager;
    RecipeManager recipeManager;
    ExerciseManager exerciseManager;

    std::shared_ptr<User> currentUser;

public:
    void loginUser(const std::string& username, const std::string& password);
    void registerUser(const std::string& username, const std::string& password, 
                      unsigned age, double weight, double height, Gender gender);
    void logoutUser();

};