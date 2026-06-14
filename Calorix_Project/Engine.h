#pragma once
#include "CalorixSystem.h"
#include "comands/CommandParser.h"

class Engine {
private:
    CalorixSystem system;
    CommandParser parser;
    bool isRunning;

public:
    Engine();

    void run();
};