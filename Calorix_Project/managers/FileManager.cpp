#include "FileManager.h"
#include <fstream>
#include <stdexcept>

std::vector<std::string> FileManager::readLines(const std::string& filename) const {
    std::vector<std::string> lines;
    std::ifstream file(filename);

    if (!file.is_open()) {
        return lines; 
    }

    std::string currentLine;
    while (std::getline(file, currentLine)) {
        if (!currentLine.empty()) {
            lines.push_back(currentLine);
        }
    }

    file.close();
    return lines;
}

void FileManager::overwriteFile(const std::string& filename, const std::vector<std::string>& lines) const {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        throw std::runtime_error("Critical Error: Could not open file for writing -> " + filename);
    }

    for (const auto& line : lines) {
        file << line << "\n";
    }

    file.close();
}

void FileManager::appendLine(const std::string& filename, const std::string& line) const {
    std::ofstream file(filename, std::ios::out | std::ios::app);

    if (!file.is_open()) {
        throw std::runtime_error("Critical Error: Could not open file for appending -> " + filename);
    }

    file << line << "\n";
    file.close();
}

bool FileManager::fileExists(const std::string& filename) const {
    std::ifstream file(filename);
    return file.good();
}