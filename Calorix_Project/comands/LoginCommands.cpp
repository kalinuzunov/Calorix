#include "LoginCommands.h"
#include "../CalorixSystem.h"

LoginCommand::LoginCommand(const std::string& username, const std::string& password)
    : username(username), password(password) {}

void LoginCommand::execute(CalorixSystem& system) {
    system.loginUser(username, password);
}

RegisterCommand::RegisterCommand(const std::string& username, const std::string& password, 
                                 unsigned age, double weight, double height, Gender gender)
    : username(username), password(password), age(age), 
      weight(weight), height(height), gender(gender) {}

void RegisterCommand::execute(CalorixSystem& system) {
    system.registerUser(username, password, age, weight, height, gender);
}

void LogoutCommand::execute(CalorixSystem& system) {
    system.logoutUser();
}