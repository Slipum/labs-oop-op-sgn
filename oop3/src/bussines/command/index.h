#ifndef OOP3_INDEX_H
#define OOP3_INDEX_H
#include <vector>

class ICommand {
public:
    virtual ~ICommand() = default;

    virtual void exec() = 0;
};

class Invoker {
    std::vector<std::unique_ptr<ICommand>> commands;
public:
    Invoker() = default;
    virtual ~Invoker() = default;

    void addCommand(std::unique_ptr<ICommand> command);
    void executeAllCommands();
    void undoAllCommands();
};

#endif //OOP3_INDEX_H
