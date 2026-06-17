#include "CalorixSystem.h"
#include "model/Admin.h"
#include "model/Trainee.h"
#include "model/Food.h"
#include "model/Password.h"
#include "model/UserProfile.h"
#include "model/UserProfileBuilder.h"
#include "model/MifflinStJeorStrategy.h"
#include "model/HarrisBenedictStrategy.h"
#include "model/WHOStrategy.h"
#include "model/CalorixExceptions.h"

#include <iostream>

#include "Constants.h"

CalorixSystem::CalorixSystem(const std::string& usersFile, const std::string& foodsFile,
                             const std::string& recipesFile, const std::string& exercisesFile,
                             const std::string& blockedUsersFile)
    : userManager(usersFile), foodManager(foodsFile),
      recipeManager(recipesFile), exerciseManager(exercisesFile),
      blockedUserManager(blockedUsersFile),
      diaryManager("food_logs.txt", "exercise_logs.txt"),
      currentUser(nullptr) {
}

void CalorixSystem::initialize() const {
    std::cout << "[SYSTEM] Calorix initialized. Data loaded.\n";

    std::vector<User> loadedUsers = userManager.loadAllUsers();

    if (loadedUsers.empty()) {
        Admin boss("Kalin_Uzunov", Password("kAlIn9.u"), UserProfile{});
        userManager.saveUser(boss);
        std::cout << "[SYSTEM] Welcome boss!\n";
    }
}

void CalorixSystem::shutdown() {
    std::cout << "[SYSTEM] Saving data... Goodbye!\n";
}

void CalorixSystem::displayHelp() const {
    std::cout << "--- Calorix Help Menu ---\n";
    if (currentUser == nullptr) {
        std::cout << "You are a Guest. Available commands:\n";
        std::cout << "- login <username> <password>\n";
        std::cout << "- register <username> <password> <age> <weight> <height> <gender(0/1)>\n";

    } else if (std::dynamic_pointer_cast<Admin>(currentUser)) {
        std::cout << "You are an Admin. Available commands:\n";
        std::cout << "- add_food <name> <cal> <prot> <carbs> <fat> <fiber>\n";
        std::cout << "- update_food <name> <new_calories>\n";
        std::cout << "- list_foods\n";
        std::cout << "- add_exercise <name> <caloriesPerHour> <muscleGroup(0-7)>\n";
        std::cout << "- list_exercises\n";
        std::cout << "- block_user <username>\n";
        std::cout << "- unblock_user <username>\n";
        std::cout << "- logout\n";

    } else {
        std::cout << "You are a Trainee. Available commands:\n";
        std::cout << "- log_food <name> <grams>\n";
        std::cout << "- list_foods\n";
        std::cout << "- log_exercise <name> <minutes>\n";
        std::cout << "- list_exercises\n";
        std::cout << "- view_summary\n";
        std::cout << "- calculate_bmi\n";
        std::cout << "- calculate_bmr\n";
        std::cout << "- logout\n";
    }
    std::cout << "- end (Closes the application)\n";
    std::cout << "-------------------------\n";
}

void CalorixSystem::loginUser(const std::string& username, const std::string& password) {
    if (currentUser != nullptr) {
        throw AuthenticationException("Already logged in.");
    }

    if (blockedUserManager.isUserBlocked(username)) {
        throw AuthenticationException("Access denied: Your account has been blocked by an Administrator.");
    }

    std::vector<User> loadedUsers = userManager.loadAllUsers();
    bool found = false;

    for (const auto& user : loadedUsers) {
        if (user.getUsername() == username && user.getPassword() == password) {
            if (username == "Kalin_Uzunov") {
                currentUser = std::make_shared<Admin>(username, Password(password), user.getProfile());
            } else {
                currentUser = std::make_shared<Trainee>(user.getUserId(), username, Password(password), user.getProfile());

                auto traineePtr = std::dynamic_pointer_cast<Trainee>(currentUser);
                diaryManager.loadUserLogs(*traineePtr, foodManager, exerciseManager);
            }
            found = true;
            break;
        }
    }

    if (!found) {
        throw InvalidPasswordException("Wrong credentials.");
    }
    std::cout << "[SYSTEM] Logged in successfully: " << username << "\n";
    displayHelp();
}

void CalorixSystem::registerUser(const std::string& username, const std::string& password,
                                 unsigned age, double weight, double height, Gender gender) {
    if (currentUser != nullptr) {
        throw AuthenticationException("Cannot register while logged in.");
    }

    std::vector<User> existingUsers = userManager.loadAllUsers();
    for (const auto& u : existingUsers) {
        if (u.getUsername() == username) {
            throw InvalidNameException("Username already exists!");
        }
    }
    UserProfile profile = UserProfileBuilder()
                            .setAge(age)
                            .setWeight(weight)
                            .setHeight(height)
                            .setGender(gender)
                            .build();

    Trainee newUser(username, Password(password), profile);

    userManager.saveUser(newUser);

    std::cout << "[SYSTEM] Registration successful for: " << username << "\n";
}

void CalorixSystem::logoutUser() {
    if (currentUser == nullptr) {
        throw AuthenticationException("No user is currently logged in.");
    }
    std::cout << "[SYSTEM] Logged out successfully.\n";
    currentUser = nullptr;
}

void CalorixSystem::blockUser(const std::string& targetUsername) {
    auto admin = std::dynamic_pointer_cast<Admin>(currentUser);
    if (!admin) {
        throw UnauthorizedAccessException("Admin privileges required to block users.");
    }

    if (blockedUserManager.isUserBlocked(targetUsername)) {
        std::cout << "[WARNING] User '" << targetUsername << "' is already blocked.\n";
        return;
    }

    blockedUserManager.blockUser(targetUsername);
    std::cout << "[ADMIN] User '" << targetUsername << "' has been successfully blocked.\n";
}

void CalorixSystem::unblockUser(const std::string& targetUsername) {
    auto admin = std::dynamic_pointer_cast<Admin>(currentUser);
    if (!admin) {
        throw UnauthorizedAccessException("Admin privileges required to unblock users.");
    }

    if (!blockedUserManager.isUserBlocked(targetUsername)) {
        std::cout << "[WARNING] User '" << targetUsername << "' is not blocked.\n";
        return;
    }

    blockedUserManager.unblockUser(targetUsername);
    std::cout << "[ADMIN] User '" << targetUsername << "' has been successfully unblocked.\n";
}

void CalorixSystem::addFood(const std::string& name, double calories, double protein, double carbs, double fat, double fiber) const {
    auto admin = std::dynamic_pointer_cast<Admin>(currentUser);
    if (!admin) {
        throw UnauthorizedAccessException("Admin privileges required to add food.");
    }

    foodManager.loadAllFoods();

    Food newFood(name, calories, protein, carbs, fat, fiber);

    foodManager.saveFood(newFood);

    std::cout << "[ADMIN] Food '" << name << "' saved with ID: " << newFood.getId() << "\n";
}

void CalorixSystem::displayAllFoods() const {
    auto foods = foodManager.loadAllFoods();
    if (foods.empty()) {
        std::cout << "Database is empty.\n";
        return;
    }

    std::cout << "\n--- Food Database ---\n";
    for (const auto& food : foods) {
        std::cout << "[" << food.getId() << "] " << food.getName()
                  << " | Cal: " << food.getCaloriesPer100g()
                  << " | P: " << food.getProteinPer100g() << "\n";
    }
}

void CalorixSystem::updateFood(const std::string& foodName, double newCalories) {
    auto admin = std::dynamic_pointer_cast<Admin>(currentUser);
    if (!admin) {
        throw UnauthorizedAccessException("Admin privileges required to update food.");
    }

    foodManager.updateFoodCalories(foodName, newCalories);

    std::cout << "[ADMIN] Food '" << foodName << "' successfully updated to " << newCalories << " kcal.\n";
}

void CalorixSystem::addExercise(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup) {
    auto admin = std::dynamic_pointer_cast<Admin>(currentUser);
    if (!admin) {
        throw UnauthorizedAccessException("Admin privileges required to add exercises.");
    }

    exerciseManager.loadAllExercises();

    Exercise newExercise(name, caloriesBurnedPerHour, muscleGroup);
    exerciseManager.saveExercise(newExercise);

    std::cout << "[ADMIN] Exercise '" << name << "' saved with ID: " << newExercise.getExerciseId() << "\n";
}

void CalorixSystem::displayAllExercises() const {
    auto exercises = exerciseManager.loadAllExercises();

    if (exercises.empty()) {
        std::cout << "Exercise database is empty.\n";
        return;
    }

    std::cout << "\n--- Exercise Database ---\n";
    for (const auto& ex : exercises) {
        std::cout << "[" << ex.getExerciseId() << "] " << ex.getName()
                  << " | Calories/Hour: " << ex.getCaloriesBurnedPerHour()
                  << " | Muscle Group (0-7): " << static_cast<int>(ex.getMuscleGroup()) << "\n";
    }
}

void CalorixSystem::setGoal(GoalType type, double targetValue, const Date& deadline) {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) {
        throw UnauthorizedAccessException("You must be a Trainee to set goals.");
    }

    std::cout << "[TRAINEE] Goal set successfully.\n";
}

void CalorixSystem::logFood(const std::string& foodName, double quantityGrams) {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) {
        throw UnauthorizedAccessException("Trainee privileges required to log food.");
    }

    std::vector<Food> allFoods = foodManager.loadAllFoods();
    bool found = false;

    for (const auto& food : allFoods) {
        if (food.getName() == foodName) {
            auto consumableItem = std::make_shared<Food>(food);
            Date today;
            FoodEntry entry(consumableItem, quantityGrams, today);

            trainee->logFood(entry);
            diaryManager.saveFoodLog(trainee->getUsername(), entry);

            found = true;

            double caloriesAdded = (quantityGrams / Constants::FoodLimits::BASE_GRAMS_UNIT) * food.getCaloriesPer100g();

            std::cout << "[TRAINEE] Successfully logged " << quantityGrams << "g of " << foodName << ".\n";
            std::cout << "          Added " << caloriesAdded << " kcal to your diary.\n";
            break;
        }
    }

    if (!found) {
        std::cout << "[ERROR] Food '" << foodName << "' not found in the database. Use 'list_foods' to see available options.\n";
    }
}

void CalorixSystem::logExercise(const std::string& exerciseName, int durationMinutes) {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) {
        throw UnauthorizedAccessException("Trainee privileges required to log exercise.");
    }

    auto allExercises = exerciseManager.loadAllExercises();
    bool found = false;

    for (const auto& exercise : allExercises) {
        if (exercise.getName() == exerciseName) {
            unsigned exId = exercise.getExerciseId();
            Date today;
            ExerciseEntry entry(exId, durationMinutes, today);

            trainee->logExercise(entry);
            diaryManager.saveExerciseLog(trainee->getUsername(), entry);

            found = true;

            std::cout << "[TRAINEE] Successfully logged " << durationMinutes << " minutes of " << exerciseName << ".\n";
            break;
        }
    }

    if (!found) {
        std::cout << "[ERROR] Exercise '" << exerciseName << "' not found in the database. Use 'list_exercises' to see available options.\n";
    }
}

void CalorixSystem::viewDailySummary() const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) {
        throw UnauthorizedAccessException("Trainee privileges required to view summary.");
    }

    Date today;
    std::string todayStr = today.toString();

    std::cout << "\n=== Daily Summary for " << trainee->getUsername() << " (" << todayStr << ") ===\n";

    double totalConsumed = Constants::Global::ZERO;
    double totalProtein = Constants::Global::ZERO;
    double totalCarbs = Constants::Global::ZERO;
    double totalFat = Constants::Global::ZERO;
    double totalFiber = Constants::Global::ZERO;

    const auto& foodDiary = trainee->getFoodDiary();

    for (const auto& entry : foodDiary) {
        if (entry.getDate().toString() == todayStr) {
            totalConsumed += entry.getTotalCalories();
            totalProtein += entry.getTotalProtein();
            totalCarbs += entry.getTotalCarbs();
            totalFat += entry.getTotalFat();
            totalFiber += entry.getTotalFiber();
        }
    }

    double totalBurned = Constants::Global::ZERO;
    const auto& exerciseDiary = trainee->getExerciseDiary();
    auto allExercises = exerciseManager.loadAllExercises();

    for (const auto& entry : exerciseDiary) {
        if (entry.getDate().toString() == todayStr) {
            unsigned targetId = entry.getExerciseId();

            for (const auto& ex : allExercises) {
                if (ex.getExerciseId() == targetId) {
                    totalBurned += (entry.getDurationMinutes() / Constants::ExerciseLimits::MINUTES_IN_HOUR) * ex.getCaloriesBurnedPerHour();
                    break;
                }
            }
        }
    }

    double netCalories = totalConsumed - totalBurned;

    std::cout << "--- Macros Consumed ---\n";
    std::cout << "Protein: " << totalProtein << "g | Carbs: " << totalCarbs
              << "g | Fat: " << totalFat << "g | Fiber: " << totalFiber << "g\n";
    std::cout << "------------------------------------\n";
    std::cout << "Calories Consumed:  " << totalConsumed << " kcal\n";
    std::cout << "Calories Burned:    " << totalBurned << " kcal\n";
    std::cout << "------------------------------------\n";
    std::cout << "Net Calories:       " << netCalories << " kcal\n";
    std::cout << "====================================\n\n";
}

void CalorixSystem::viewProgress() const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) {
        throw UnauthorizedAccessException("Trainee privileges required to view progress.");
    }

    std::cout << "[TRAINEE] Displaying goal progress...\n";
}

void CalorixSystem::calculateBMI() const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) {
        throw UnauthorizedAccessException("Trainee privileges required to calculate BMI.");
    }

    const UserProfile& profile = trainee->getProfile();
    double weight = profile.getWeight();

    double heightMeters = profile.getHeight() / Constants::HealthFormulas::CENTIMETERS_IN_METER;

    if (heightMeters <= Constants::Global::ZERO) {
        std::cout << "[ERROR] Invalid height in profile.\n";
        return;
    }

    double bmi = weight / (heightMeters * heightMeters);

    std::cout << "\n=== BMI Calculator ===\n";
    std::cout << "Height: " << profile.getHeight() << " cm | Weight: " << weight << " kg\n";
    std::cout << "Your BMI: " << bmi << "\n";

    std::cout << "Category: ";
    if (bmi < Constants::HealthFormulas::BMI::UNDERWEIGHT_THRESHOLD) {
        std::cout << "Underweight\n";
    } else if (bmi < Constants::HealthFormulas::BMI::NORMAL_WEIGHT_THRESHOLD) {
        std::cout << "Normal weight\n";
    } else if (bmi < Constants::HealthFormulas::BMI::OVERWEIGHT_THRESHOLD) {
        std::cout << "Overweight\n";
    } else {
        std::cout << "Obese\n";
    }
    std::cout << "======================\n\n";
}

void CalorixSystem::calculateBMR() const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) {
        throw UnauthorizedAccessException("Trainee privileges required to calculate BMR.");
    }

    const UserProfile& profile = trainee->getProfile();

    MifflinStJeorStrategy mifflin;
    HarrisBenedictStrategy harris;
    WHOStrategy who;

    std::cout << "\n=== BMR Calculator (Basal Metabolic Rate) ===\n";
    std::cout << "Profile Stats -> Age: " << profile.getAge()
              << " | Weight: " << profile.getWeight()
              << "kg | Height: " << profile.getHeight() << "cm\n\n";

    std::cout << "Calories needed to maintain basic bodily functions at rest:\n";
    std::cout << "- Mifflin-St Jeor formula: " << mifflin.calculateBMR(profile) << " kcal/day\n";
    std::cout << "- Harris-Benedict formula: " << harris.calculateBMR(profile) << " kcal/day\n";
    std::cout << "- WHO guidelines formula:  " << who.calculateBMR(profile) << " kcal/day\n";
    std::cout << "===============================================\n\n";
}

void CalorixSystem::generateWorkoutPlan(int durationMinutes) const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) {
        throw UnauthorizedAccessException("Trainee privileges required to generate workout plan.");
    }

    std::cout << "[TRAINEE] Generating " << durationMinutes << " min workout plan (Knapsack Algorithm)...\n";
}

void CalorixSystem::addToFavorites(const std::string& exerciseName) {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) {
        throw UnauthorizedAccessException("Trainee privileges required to add favorites.");
    }

    std::cout << "[TRAINEE] Added '" << exerciseName << "' to favorites.\n";
}

void CalorixSystem::viewFavorites() const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) {
        throw UnauthorizedAccessException("Trainee privileges required to view favorites.");
    }

    std::cout << "[TRAINEE] Displaying favorite exercises...\n";
}