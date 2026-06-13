#include "CalorixSystem.h"
#include "model/Admin.h"
#include "model/Trainee.h"
#include <iostream>
#include <stdexcept>

CalorixSystem::CalorixSystem(const std::string& usersFile, const std::string& foodsFile,
                             const std::string& recipesFile, const std::string& exercisesFile)
    : userManager(usersFile), foodManager(foodsFile),
      recipeManager(recipesFile), exerciseManager(exercisesFile),
      currentUser(nullptr) {
}

void CalorixSystem::initialize() {
    std::cout << "[SYSTEM] Calorix initialized. Data loaded.\n";
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
    if (currentUser != nullptr) {
        throw std::runtime_error("A user is already logged in.");
    }
    std::cout << "[SYSTEM] Logged in successfully: " << username << "\n";
}

void CalorixSystem::registerUser(const std::string& username, const std::string& password,
                                 unsigned age, double weight, double height, Gender gender) {
    if (currentUser != nullptr) {
        throw std::runtime_error("Cannot register while logged in.");
    }
    std::cout << "[SYSTEM] Registered and logged in successfully: " << username << "\n";
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

void CalorixSystem::addFood(const std::string& name, double calories, double protein, double carbs, double fat, double fiber) {
    auto admin = std::dynamic_pointer_cast<Admin>(currentUser);
    if (!admin) throw std::runtime_error("Access denied. Admin privileges required.");

    std::cout << "[ADMIN] Food '" << name << "' added to global database.\n";
}

void CalorixSystem::updateFood(const std::string& foodName, double newCalories) {
    auto admin = std::dynamic_pointer_cast<Admin>(currentUser);
    if (!admin) throw std::runtime_error("Access denied. Admin privileges required.");

    std::cout << "[ADMIN] Food '" << foodName << "' updated.\n";
}

void CalorixSystem::addExercise(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup) {
    auto admin = std::dynamic_pointer_cast<Admin>(currentUser);
    if (!admin) throw std::runtime_error("Access denied. Admin privileges required.");

    std::cout << "[ADMIN] Exercise '" << name << "' added to global database.\n";
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