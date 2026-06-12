#pragma once
#include "ICommand.h"

class HelpCommand : public ICommand {
public:
    HelpCommand() = default;
    void execute(CalorixSystem& system) override;
};

class EndCommand : public ICommand {
public:
    EndCommand() = default;
    void execute(CalorixSystem& system) override;
};