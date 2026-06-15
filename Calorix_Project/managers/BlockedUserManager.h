#pragma once
#include "FileManager.h"
#include <string>

class BlockedUserManager : public FileManager {
private:
    std::string filename;

public:
    BlockedUserManager(const std::string& dbFilename);

    bool isUserBlocked(const std::string& username) const;
    void blockUser(const std::string& username) const;
    void unblockUser(const std::string& username) const;
};