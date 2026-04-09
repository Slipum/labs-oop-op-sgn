#ifndef COMMAND_H
#define COMMAND_H

#include <vector>

#include "../bussines/logic.h"

class ICommand : public UtilsCommand {
protected:
    vector<Figure*>* figures;
    void setNameFigure(Figure* f);
    void IsEmptyFigures();
public:
    ICommand(vector<Figure*>* figures) : figures(figures) {};
    virtual ~ICommand() = default;

    virtual void exec() = 0;
    virtual string intro() {};
};

#endif // COMMAND_H