#include "CalorixSystem.h"
#include "model/Admin.h"
#include "model/Trainee.h"
#include "model/Food.h"
#include <iostream>
#include <stdexcept>
#include "model/Password.h"
#include "model/UserProfile.h"
#include "model/UserProfileBuilder.h"

CalorixSystem::CalorixSystem(const std::string& usersFile, const std::string& foodsFile,
                             const std::string& recipesFile, const std::string& exercisesFile)
    : userManager(usersFile), foodManager(foodsFile),
      recipeManager(recipesFile), exerciseManager(exercisesFile),
      currentUser(nullptr) {
}

void CalorixSystem::initialize()const {
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
        std::cout << "- register <username> <password> <age> <weight> <height> <gender>\n";
    } else if (std::dynamic_pointer_cast<Admin>(currentUser)) {
        std::cout << "You are an Admin. Available commands:\n";
        std::cout << "- add_food <name> <cal> <prot> <carbs> <fat> <fiber>\n";
        std::cout << "- list_foods\n";
        std::cout << "- add_exercise <name> <caloriesPerHour> <muscleGroup(0-7)>\n";
        std::cout << "- list_exercises\n";
        std::cout << "- block_user <username>\n";
        std::cout << "- logout\n";
    } else {
        std::cout << "You are a Trainee. Available commands:\n";
        std::cout << "- log_food <name> <grams>\n";
        std::cout << "- log_exercise <name> <minutes>\n";
        std::cout << "- view_summary\n";
        std::cout << "- logout\n";
    }
    std::cout << "- end (Closes the application)\n";
    std::cout << "-------------------------\n";
}


void CalorixSystem::loginUser(const std::string& username, const std::string& password) {
    if (currentUser != nullptr) throw std::runtime_error("Already logged in.");

    std::vector<User> loadedUsers = userManager.loadAllUsers();
    bool found = false;

    for (const auto& user : loadedUsers) {
        if (user.getUsername() == username && user.getPassword() == password) {
            if (username == "Kalin_Uzunov") {
                currentUser = std::make_shared<Admin>(username, Password(password), user.getProfile());
            } else {
                currentUser = std::make_shared<Trainee>(user.getUserId(), username, Password(password), user.getProfile());
            }
            found = true;
            break;
        }
    }

    if (!found) throw std::runtime_error("Wrong credentials.");
    std::cout << "[SYSTEM] Logged in successfully: " << username << "\n";
    displayHelp();
}

void CalorixSystem::registerUser(const std::string& username, const std::string& password,
                                 unsigned age, double weight, double height, Gender gender) {
    if (currentUser != nullptr) {
        throw std::runtime_error("Cannot register while logged in.");
    }

    std::vector<User> existingUsers = userManager.loadAllUsers();
    for (const auto& u : existingUsers) {
        if (u.getUsername() == username) {
            throw std::runtime_error("Username already exists!");
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
        throw std::runtime_error("No user is currently logged in.");
    }
    std::cout << "[SYSTEM] Logged out successfully.\n";
    currentUser = nullptr;
}


void CalorixSystem::blockUser(const std::string& targetUsername) {
    auto admin = std::dynamic_pointer_cast<Admin>(currentUser);
    if (!admin) throw std::runtime_error("Access denied. Admin privileges required.");

    std::cout << "[ADMIN] User " << targetUsername << " has been blocked.\n";
}

void CalorixSystem::addFood(const std::string& name, double calories, double protein, double carbs, double fat, double fiber) const {
    auto admin = std::dynamic_pointer_cast<Admin>(currentUser);
    if (!admin) throw std::runtime_error("Access denied. Admin privileges required.");

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
    if (!admin) throw std::runtime_error("Access denied. Admin privileges required.");

    std::cout << "[ADMIN] Food '" << foodName << "' updated.\n";
}

void CalorixSystem::addExercise(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup) {
    auto admin = std::dynamic_pointer_cast<Admin>(currentUser);
    if (!admin) {
        throw std::runtime_error("Access denied. Admin privileges required.");
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
    if (!trainee) throw std::runtime_error("Access denied. You must be a Trainee to set goals.");

    std::cout << "[TRAINEE] Goal set successfully.\n";
}

void CalorixSystem::logFood(const std::string& foodName, double quantityGrams) {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) throw std::runtime_error("Access denied. Trainee privileges required.");

    std::cout << "[TRAINEE] Logged " << quantityGrams << "g of " << foodName << ".\n";
}

void CalorixSystem::logExercise(const std::string& exerciseName, int durationMinutes) {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) throw std::runtime_error("Access denied.");

    std::cout << "[TRAINEE] Logged " << durationMinutes << " minutes of " << exerciseName << ".\n";
}

void CalorixSystem::viewDailySummary() const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) throw std::runtime_error("Access denied.");

    std::cout << "[TRAINEE] Displaying daily summary...\n";
}

void CalorixSystem::viewProgress() const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) throw std::runtime_error("Access denied.");

    std::cout << "[TRAINEE] Displaying goal progress...\n";
}

void CalorixSystem::calculateBMI() const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) throw std::runtime_error("Access denied.");

    std::cout << "[TRAINEE] Calculating BMI...\n";
}

void CalorixSystem::calculateBMR() const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) throw std::runtime_error("Access denied.");

    std::cout << "[TRAINEE] Calculating BMR...\n";
}

void CalorixSystem::generateWorkoutPlan(int durationMinutes) const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) throw std::runtime_error("Access denied.");

    std::cout << "[TRAINEE] Generating " << durationMinutes << " min workout plan (Knapsack Algorithm)...\n";
}

void CalorixSystem::addToFavorites(const std::string& exerciseName) {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) throw std::runtime_error("Access denied.");

    std::cout << "[TRAINEE] Added '" << exerciseName << "' to favorites.\n";
}

void CalorixSystem::viewFavorites() const {
    auto trainee = std::dynamic_pointer_cast<Trainee>(currentUser);
    if (!trainee) throw std::runtime_error("Access denied.");

    std::cout << "[TRAINEE] Displaying favorite exercises...\n";
}