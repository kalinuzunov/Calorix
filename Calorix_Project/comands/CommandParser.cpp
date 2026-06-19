#include "CommandParser.h"
#include "LoginCommands.h"
#include "GeneralCommands.h"
#include "AdminCommands.h"
#include "TraineeCommands.h"
#include "../model/CalorixExceptions.h"
#include "../Constants.h"
#include <string>
#include <stdexcept>

std::vector<std::string> CommandParser::splitArguments(const std::string& input) const {
    std::vector<std::string> args;
    std::string currentWord = "";

    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] == ' ') {
            if (!currentWord.empty()) {
                args.push_back(currentWord);
                currentWord = "";
            }
        } else {
            currentWord += input[i];
        }
    }

    if (!currentWord.empty()) {
        args.push_back(currentWord);
    }

    return args;
}

std::unique_ptr<ICommand> CommandParser::parse(const std::string& input) const {
    auto args = splitArguments(input);

    if (args.empty()) {
        return nullptr;
    }

    std::string cmdName = args[0];

    constexpr size_t NO_ADDITIONAL_ARGS = 1;
    constexpr size_t SET_GOAL_EXPECTED_ARGS = 4;

    if (cmdName == "help") return std::make_unique<HelpCommand>();
    if (cmdName == "end") return std::make_unique<EndCommand>();
    if (cmdName == "list_foods") return std::make_unique<ListFoodsCommand>();
    if (cmdName == "list_exercises") return std::make_unique<ListExercisesCommand>();

    if (cmdName == "login") {
        if (args.size() != Constants::Database::LOGIN_RECORD_FIELDS) {
            throw InvalidCommandException("Usage: login <username> <password>");
        }
        return std::make_unique<LoginCommand>(args[1], args[2]);
    }

    if (cmdName == "logout") return std::make_unique<LogoutCommand>();

    if (cmdName == "register") {
        if (args.size() != Constants::Database::REGISTER_RECORD_FIELDS) {
            throw InvalidCommandException("Usage: register <username> <password> <age> <weight> <height> <gender(MALE/FEMALE/OTHER)>");
        }
        try {
            std::string username = args[1];
            std::string password = args[2];
            unsigned age = std::stoul(args[3]);
            double weight = std::stod(args[4]);
            double height = std::stod(args[5]);

            Gender gender;
            if (args[6] == "MALE") gender = Gender::MALE;
            else if (args[6] == "FEMALE") gender = Gender::FEMALE;
            else if (args[6] == "OTHER") gender = Gender::OTHER;
            else throw std::invalid_argument("Invalid gender format.");

            return std::make_unique<RegisterCommand>(username, password, age, weight, height, gender);
        } catch (...) {
            throw InvalidCommandException("Invalid input data for registration!");
        }
    }

    if (cmdName == "block_user") {
        if (args.size() != Constants::Database::BLOCK_RECORD_FIELDS) {
            throw InvalidCommandException("Usage: block_user <username>");
        }
        return std::make_unique<BlockUserCommand>(args[1]);
    }

    if (cmdName == "unblock_user") {
        if (args.size() != Constants::Database::BLOCK_RECORD_FIELDS) {
            throw InvalidCommandException("Usage: unblock_user <username>");
        }
        return std::make_unique<UnblockUserCommand>(args[1]);
    }

    if (cmdName == "add_food") {
        if (args.size() != Constants::Database::FOOD_RECORD_FIELDS) {
            throw InvalidCommandException("Usage: add_food <name> <cal> <prot> <carbs> <fat> <fiber>");
        }
        try {
            std::string foodName = args[1];
            double calories = std::stod(args[2]);
            double protein = std::stod(args[3]);
            double carbs = std::stod(args[4]);
            double fat = std::stod(args[5]);
            double fiber = std::stod(args[6]);

            return std::make_unique<AddFoodCommand>(foodName, calories, protein, carbs, fat, fiber);
        } catch (const std::invalid_argument& e) {
            throw InvalidCommandException("Calories and macros must be valid numbers!");
        }
    }

    if (cmdName == "update_food") {
        if (args.size() != Constants::Database::UPDATE_FOOD_RECORD_FIELDS) {
            throw InvalidCommandException("Usage: update_food <name> <new_calories>");
        }
        try {
            std::string foodName = args[1];
            double newCalories = std::stod(args[2]);
            return std::make_unique<UpdateFoodCommand>(foodName, newCalories);
        } catch (const std::invalid_argument& e) {
            throw InvalidCommandException("Calories must be a valid number!");
        }
    }

    if (cmdName == "add_exercise") {
        if (args.size() != Constants::Database::EXERCISE_RECORD_FIELDS) {
            throw InvalidCommandException("Usage: add_exercise <name> <caloriesPerHour> <muscleGroup(CHEST/BACK/LEGS/SHOULDERS/ARMS/CORE/CARDIO)>");
        }
        try {
            std::string exName = args[1];
            double calPerHour = std::stod(args[2]);

            MuscleGroup group;
            if (args[3] == "CHEST") group = MuscleGroup::CHEST;
            else if (args[3] == "BACK") group = MuscleGroup::BACK;
            else if (args[3] == "LEGS") group = MuscleGroup::LEGS;
            else if (args[3] == "SHOULDERS") group = MuscleGroup::SHOULDERS;
            else if (args[3] == "ARMS") group = MuscleGroup::ARMS;
            else if (args[3] == "CORE") group = MuscleGroup::CORE;
            else if (args[3] == "CARDIO") group = MuscleGroup::CARDIO;
            else throw std::invalid_argument("Invalid muscle group.");

            return std::make_unique<AddExerciseCommand>(exName, calPerHour, group);
        } catch (const std::invalid_argument& e) {
            throw InvalidCommandException("Invalid input for add_exercise!");
        }
    }

    if (cmdName == "log_food") {
        if (args.size() != Constants::Database::ADD_FOOD_RECORD_FIELDS) {
            throw InvalidCommandException("Usage: log_food <food_name> <grams>");
        }
        return std::make_unique<LogFoodCommand>(args[1], std::stod(args[2]));
    }

    if (cmdName == "log_exercise") {
        if (args.size() != Constants::Database::ADD_EXCERCISE_FIELDS) {
            throw InvalidCommandException("Usage: log_exercise <exercise_name> <duration_minutes>");
        }
        return std::make_unique<LogExerciseCommand>(args[1], std::stoi(args[2]));
    }

    if (cmdName == "view_summary") {
        if (args.size() > NO_ADDITIONAL_ARGS) {
            throw InvalidCommandException("Usage: view_summary (no arguments needed)");
        }
        return std::make_unique<ViewDailySummaryCommand>();
    }

    if (cmdName == "calculate_bmi") {
        if (args.size() > NO_ADDITIONAL_ARGS) {
            throw InvalidCommandException("Usage: calculate_bmi (no arguments needed)");
        }
        return std::make_unique<CalculateBMICommand>();
    }

    if (cmdName == "calculate_bmr") {
        if (args.size() > NO_ADDITIONAL_ARGS) {
            throw InvalidCommandException("Usage: calculate_bmr (no arguments needed)");
        }
        return std::make_unique<CalculateBMRCommand>();
    }

    if (cmdName == "view_progress") {
        if (args.size() > NO_ADDITIONAL_ARGS) {
            throw InvalidCommandException("Usage: view_progress (no arguments needed)");
        }
        return std::make_unique<ViewProgressCommand>();
    }

    if (cmdName == "set_goal") {
        if (args.size() != SET_GOAL_EXPECTED_ARGS) {
            throw InvalidCommandException("Usage: set_goal <type(WEIGHT_LOSS/BULKING/MAINTENANCE)> <targetValue> <deadline(YYYY-MM-DD)>");
        }
        try {
            GoalType type;
            if (args[1] == "WEIGHT_LOSS") type = GoalType::WEIGHT_LOSS;
            else if (args[1] == "BULKING") type = GoalType::BULKING;
            else if (args[1] == "MAINTENANCE") type = GoalType::MAINTENANCE;
            else throw std::invalid_argument("Invalid goal type.");

            double targetValue = std::stod(args[2]);
            Date deadline(args[3]);

            return std::make_unique<SetGoalCommand>(type, targetValue, deadline);
        } catch (const std::invalid_argument& e) {
            throw InvalidCommandException("Invalid input data! Type must be text (e.g., WEIGHT_LOSS) and target must be a number.");
        }
    }

    throw InvalidCommandException("Unknown command: " + cmdName + ". Type 'help' to see available commands.");
}