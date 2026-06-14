#include "Engine.h"
#include <iostream>
#include <string>

Engine::Engine()
    : system("users.txt", "foods.txt", "recipes.txt", "exercises.txt"),
      isRunning(true) {
}

void Engine::run() {
    system.initialize();
    std::cout << "\n=== Welcome to Calorix! ===\n";
    std::cout << "Type 'help' to see available commands.\n";

    while (isRunning) {
        std::cout << "\nCalorix> ";
        
        std::string input;
        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input == "end") {
            isRunning = false;
            continue;
        }

        try {
            auto command = parser.parse(input);
            if (command != nullptr) {
                command->execute(system);
            }
        }
        catch (const std::exception& e) {
            std::cout << "[ERROR]: " << e.what() << "\n";
        }
    }

    system.shutdown();
}