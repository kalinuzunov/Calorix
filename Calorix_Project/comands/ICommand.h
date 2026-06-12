#pragma once

class CalorixSystem;

class ICommand {
    public:
    virtual ~ICommand() {};

    virtual void execute(CalorixSystem& system) = 0;
};
