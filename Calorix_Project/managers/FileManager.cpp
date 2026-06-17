#include "FileManager.h"
#include "../model/CalorixExceptions.h"
#include <fstream>
#include <iostream>

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
        throw InvalidCommandException("Critical Error: Could not open file for writing -> " + filename);
    }

    for (const auto& line : lines) {
        file << line << "\n";
    }

    file.close();
}

void FileManager::appendLine(const std::string& filename, const std::string& line) const {
    std::ofstream file(filename, std::ios::out | std::ios::app);

    if (!file.is_open()) {
        throw InvalidCommandException("Critical Error: Could not open file for appending -> " + filename);
    }

    file << line << "\n";
    file.close();
}

bool FileManager::fileExists(const std::string& filename) const {
    std::ifstream file(filename);
    return file.good();
}

std::vector<std::string> FileManager::split(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start));

    return tokens;
}