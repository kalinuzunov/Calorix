#pragma once
#include <string>
#include <vector>

class FileManager {
protected:
    std::vector<std::string> readLines(const std::string& filename) const;

    void overwriteFile(const std::string& filename, const std::vector<std::string>& lines) const;

    void appendLine(const std::string& filename, const std::string& line) const;

    bool fileExists(const std::string& filename) const;

    std::vector<std::string> split(const std::string& str, char delimiter) const;
};