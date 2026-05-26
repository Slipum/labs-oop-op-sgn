#include "index.h"

#include <iostream>
#include <ostream>

void Invoker::executeAllCommands() {
    for (auto& command : commands) {
        command->exec();
    }
}

void Invoker::addCommand(std::unique_ptr<ICommand> command) {
    commands.push_back(std::move(command));
}

void Invoker::undoAllCommands() {
    while (commands.size() != 0)
        commands.pop_back();
}