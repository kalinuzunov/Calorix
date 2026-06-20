# Calorix - Advanced Fitness & Diet Tracking System

Calorix is a comprehensive, console-based Object-Oriented C++ application designed to help users track their daily caloric intake, monitor exercise routines, and achieve their personal fitness goals.

The system features role-based access control (Admin and Trainee) and persists data using a robust, custom-built file management system.

## 🚀 Key Features

### 👤 Trainee (User) Features
* **Daily Diary:** Log food consumption and completed exercises.
* **Fitness Goals:** Set customized goals (Weight Loss, Bulking, Maintenance) with specific deadlines.
* **Health Calculators:** Dynamically calculate BMI and Basal Metabolic Rate (BMR) using multiple scientific formulas (Mifflin-St Jeor, Harris-Benedict, WHO guidelines).
* **Workout Generation:** Automatically generate an optimal workout plan for a given timeframe using **Dynamic Programming (0-1 Knapsack Problem)**.
* **Favorites:** Save and view favorite exercises for quick access.
* **Progress Tracking:** View daily nutritional summaries (macros and net calories) and long-term goal progress.

### 🛡️ Admin Features
* **Database Management:** Add and update nutritional information for foods.
* **Exercise Management:** Add new exercises categorized by target muscle groups.
* **Moderation:** Block or unblock specific users from accessing the system.

## 🏗️ Software Architecture & OOP Highlights

This project was built with a strong emphasis on **Clean Code**, **SOLID principles**, and modern C++ practices (Memory management via `std::shared_ptr` and `std::unique_ptr` - zero raw pointers or memory leaks).

### Design Patterns Implemented:
1. **Command Pattern:** The entire CLI is driven by encapsulated command objects (e.g., `LogFoodCommand`, `CalculateBMRCommand`), making the system highly extensible and adhering to the Open/Closed Principle.
2. **Strategy Pattern:** Different BMR calculation algorithms are abstracted behind an `ICalorieCalculator` interface, allowing dynamic swapping of calculation strategies at runtime.
3. **Builder Pattern:** The `UserProfileBuilder` is utilized to construct complex user profile objects safely and cleanly.
4. **Composite Pattern (Core Engine):** The architecture includes an `IConsumable` interface, designed to handle both simple `Food` items and complex `Recipe` objects. *Note: The recipe engine is built into the backend as future-proofing for upcoming UI integrations.*

## 💾 Data Persistence
The system uses a custom `FileManager` hierarchy to handle CRUD operations across multiple text-based databases:
* `users.txt`, `blocked_users.txt`
* `foods.txt`, `exercises.txt`
* `food_logs.txt`, `exercise_logs.txt`
* `goals.txt`, `favorites.txt`

## 🛠️ How to Compile and Run

1. Ensure you have a modern C++ compiler installed (C++17 or higher recommended).
2. Open your terminal and navigate to the project directory.
3. Compile the project using `g++` (or your preferred IDE/build system):
   `g++ -std=c++17 main.cpp src/*.cpp src/managers/*.cpp src/commands/*.cpp src/model/*.cpp -o Calorix`
4. Run the executable:
   `./Calorix`
5. Type `help` in the console to see the list of available commands.

## 💻 Usage Examples (Quick Start)

Here is a quick walkthrough to demonstrate the core flows of the application.

### 1. Admin Workflow (Populating the Database)
Log in with the Super Admin credentials to set up basic foods and exercises. *(Note: Replace `<Admin_Username>` with the exact Super Admin constant configured in `Constants.h`)*.

```text
login <Admin_Username> <Admin_Password>
add_food Chicken_Breast 165 31 0 3.6 0
add_exercise Running 600 CARDIO
add_exercise Bench_Press 200 CHEST
list_foods
list_exercises
logout
```

### 2. Trainee Workflow (Tracking & Planning)
Register a new user, set a fitness goal, log daily activities, and dynamically generate a workout plan.
*(Note: Passwords must be at least 8 characters and contain an uppercase, lowercase, digit, and special character).*

```text
register <your_username> <your_password> <your_age> <your_weight> <your_height> <your_gender>
login <your_username> <your_password>
set_goal WEIGHT_LOSS 80.0 2026-12-31
calculate_bmr
log_food Chicken_Breast 250
log_exercise Running 40
generate_workout_plan 45
view_summary
logout
```