#include "CommandParser.h"
#include "LoginCommands.h"
#include "GeneralCommands.h"
#include "AdminCommands.h"
#include "../model/CalorixExceptions.h"
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

    if (cmdName == "help") return std::make_unique<HelpCommand>();
    if (cmdName == "end") return std::make_unique<EndCommand>();
    if (cmdName == "logout") return std::make_unique<LogoutCommand>();
    if (cmdName == "list_foods") return std::make_unique<ListFoodsCommand>();


    if (cmdName == "login") {
        if (args.size() != 3) {
            throw InvalidCommandException("Usage: login <username> <password>");
        }
        return std::make_unique<LoginCommand>(args[1], args[2]);
    }

    if (cmdName == "add_food") {
        if (args.size() != 7) {
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