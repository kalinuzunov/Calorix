#include "BlockedUserManager.h"
#include <fstream>

BlockedUserManager::BlockedUserManager(const std::string& dbFilename) : filename(dbFilename) {}

bool BlockedUserManager::isUserBlocked(const std::string& username) const {
    std::vector<std::string> blockedUsers = readLines(filename);
    for (const auto& name : blockedUsers) {
        if (name == username) {
            return true;
        }
    }
    return false;
}

void BlockedUserManager::blockUser(const std::string& username) const {
    if (!isUserBlocked(username)) {
        appendLine(filename, username);
    }
}

void BlockedUserManager::unblockUser(const std::string& username) const {
    if (!isUserBlocked(username)) return;

    std::vector<std::string> blockedUsers = readLines(filename);

    std::ofstream outFile(filename, std::ios::trunc);
    for (const auto& name : blockedUsers) {
        if (name != username) {
            outFile << name << "\n";
        }
    }
}