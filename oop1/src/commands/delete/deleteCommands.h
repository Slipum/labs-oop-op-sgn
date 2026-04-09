#ifndef DELETECOMMANDS_H
#define DELETECOMMANDS_H

#include "../menu/menu.h"

class DeleteCommand : public ICommand {
protected:
    int index;
    MenuCommand* owner;
    void deleteClass();
public:
    DeleteCommand(MenuCommand* owner, vector<Figure*>* figures);

    virtual ~DeleteCommand() = default;
};

class DeletePerNumCommand : public DeleteCommand {
public:
    DeletePerNumCommand(MenuCommand* owner, vector<Figure*>* figures);

    void exec() override;
    string intro() override;
private:
    void InputNum();
};

class DeletePerAreaCommand : public DeleteCommand {
    double area;
    vector<int> indexes;
public:
    DeletePerAreaCommand(MenuCommand* owner, vector<Figure*>* figures);

    void exec() override;
    string intro() override;
private:
    void InputArea();
    void getIndexes();
    void IsEmptyIndexes();
};

#endif //DELETECOMMANDS_H
