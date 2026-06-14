#pragma once
#include <string>
#include <memory>
#include <vector>
#include "ICommand.h"

class CommandParser {
private:
    std::vector<std::string> splitArguments(const std::string& input) const;

public:
    CommandParser() = default;

    std::unique_ptr<ICommand> parse(const std::string& input) const;
};