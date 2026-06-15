#include "CommandParser.h"
#include "LoginCommands.h"
#include "GeneralCommands.h"
#include "AdminCommands.h"
#include "../model/CalorixExceptions.h"
#include <string>
#include <stdexcept>
#include "../Constants.h"

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

    if (cmdName == "help") return std::make_unique<HelpCommand>();
    if (cmdName == "end") return std::make_unique<EndCommand>();
    if (cmdName == "logout") return std::make_unique<LogoutCommand>();
    if (cmdName == "list_foods") return std::make_unique<ListFoodsCommand>();
    if (cmdName == "list_exercises") return std::make_unique<ListExercisesCommand>();

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

    if (cmdName == "register") {
        if (args.size() != Constants::Database::REGISTER_RECORD_FIELDS) {
            throw InvalidCommandException("Usage: register <username> <password> <age> <weight> <height> <gender(0/1)>");
        }

        try {
            std::string username = args[1];
            std::string password = args[2];
            unsigned age = std::stoul(args[3]);
            double weight = std::stod(args[4]);
            double height = std::stod(args[5]);
            Gender gender = static_cast<Gender>(std::stoi(args[6]));

            return std::make_unique<RegisterCommand>(username, password, age, weight, height, gender);
        } catch (...) {
            throw InvalidCommandException("Invalid input data for registration!");
        }
    }

    if (cmdName == "add_exercise") {
        if (args.size() != Constants::Database::EXERCISE_RECORD_FIELDS) {
            throw InvalidCommandException("Usage: add_exercise <name> <caloriesPerHour> <muscleGroup(0-7)>");
        }

        try {
            std::string exName = args[1];
            double calPerHour = std::stod(args[2]);
            MuscleGroup group = static_cast<MuscleGroup>(std::stoi(args[3]));

            return std::make_unique<AddExerciseCommand>(exName, calPerHour, group);

        } catch (const std::invalid_argument& e) {
            throw InvalidCommandException("Calories per hour and muscle group must be valid numbers!");
        }
    }

    if (cmdName == "login") {
        if (args.size() != Constants::Database::LOGIN_RECORD_FIELDS) {
            throw InvalidCommandException("Usage: login <username> <password>");
        }
        return std::make_unique<LoginCommand>(args[1], args[2]);
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

    throw InvalidCommandException("Unknown command: " + cmdName + ". Type 'help' to see available commands.");
}