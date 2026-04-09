#ifndef PRINTCOMMANDS_H
#define PRINTCOMMANDS_H

#include "../command.h"
#include "../menu/menu.h"

enum PrintBy {
    PARAMS = 1,
    AREAS,
};

class PrintAllCommand: public ICommand {
protected:
    MenuCommand* owner;
public:
    PrintAllCommand(MenuCommand* owner, vector<Figure*>* figures);

    void PrintBy();
    virtual void by(int index);
    void exec() override;

    virtual ~PrintAllCommand() = default;
};

class PrintAllParamsCommand: public PrintAllCommand {
public:
    PrintAllParamsCommand(MenuCommand* owner, vector<Figure*>* figures);

    void by(int index) override;
    void exec() override;
    string intro() override;
};

class PrintAllAreasCommand: public PrintAllCommand {
public:
    PrintAllAreasCommand(MenuCommand* owner, vector<Figure*>* figures);

    void by(int index) override;
    void exec() override;
    string intro() override;
};

#endif //PRINTCOMMANDS_H
