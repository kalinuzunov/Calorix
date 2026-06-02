#include "Admin.h"
#include <iostream>

Admin::Admin(const std::string& username, const std::string& password, const UserProfile& profile)
    : User(username, password, profile) {
    // Конструкторът просто предава данните на бащата (User)
}

void Admin::blockUser(const std::string& targetUsername) {
    std::cout << "Admin " << getUsername() << " is blocking user: " << targetUsername << std::endl;
    // Тук по-късно ще извикаме логиката за триене от системата
}

void Admin::addFood(const std::string& name, double caloriesPer100g, double proteinPer100g,
                    double carbsPer100g, double fatPer100g, double fiberPer100g) {
    std::cout << "Adding food: " << name << " with " << caloriesPer100g << " kcal." << std::endl;
}

void Admin::addExercise(const std::string& name, double caloriesBurnedPerHour, MuscleGroup muscleGroup) {
    std::cout << "Adding exercise: " << name << std::endl;
}

void Admin::updateFood(const std::string& foodName, double newCalories) {
    std::cout << "Updating food " << foodName << " to " << newCalories << " kcal." << std::endl;
}