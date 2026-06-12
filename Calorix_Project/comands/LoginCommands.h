#pragma once
#include "ICommand.h"
#include "../model/Enums.h"
#include <string>

class LoginCommand : public ICommand {
private:
    std::string username;
    std::string password;

public:
    LoginCommand(const std::string& username, const std::string& password);
    void execute(CalorixSystem& system) override;
};

class RegisterCommand : public ICommand {
private:
    std::string username;
    std::string password;
    unsigned age;
    double weight;
    double height;
    Gender gender;

public:
    RegisterCommand(const std::string& username, const std::string& password, 
                    unsigned age, double weight, double height, Gender gender);
    void execute(CalorixSystem& system) override;
};

class LogoutCommand : public ICommand {
public:
    LogoutCommand() = default;
    void execute(CalorixSystem& system) override;
};