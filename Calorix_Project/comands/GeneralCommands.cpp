#include "GeneralCommands.h"
#include "../CalorixSystem.h"

void HelpCommand::execute(CalorixSystem& system) {
    system.displayHelp();
}

void EndCommand::execute(CalorixSystem& system) {
    system.shutdown();
}