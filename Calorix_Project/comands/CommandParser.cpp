#include "CommandParser.h"
#include "LoginCommands.h"
#include "GeneralCommands.h"
#include "../model/CalorixExceptions.h"

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

    if (cmdName == "login") {
        if (args.size() != 3) {
            throw InvalidCommandException("Usage: login <username> <password>");
        }
        return std::make_unique<LoginCommand>(args[1], args[2]);
    }

    throw InvalidCommandException("Unknown command: " + cmdName + ". Type 'help' to see available commands.");
}