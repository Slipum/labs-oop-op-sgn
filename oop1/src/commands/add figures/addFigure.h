#ifndef ADDFIGURE_H
#define ADDFIGURE_H

#include "../menu/menuCommand.h"

#include <map>

#define ERROR 8

enum FigureType {
    CIRCLE = 1,
    RECTANGLE,
    TRIANGLE,
    POLYGON,
};

class AddFigureCommand : public ICommand {
    MenuCommand* owner;
    int currentTypeFigure;

    void printFigureTypes();
    void InputTypeFigure();
protected:
    map<int, unique_ptr<ICommand>> figureCommand;
public:
    AddFigureCommand(MenuCommand* owner, vector<Figure*>* f);

    void exec() override;
    string intro() override;
};

class AddCircleCommand : public ICommand {
public:
    AddCircleCommand(vector<Figure*>* f);

    void exec() override;
    string intro() override;
};

class AddPolygonCommand : public ICommand {
    void setPolygonCorner(vector<coord>* corners, string corner);
public:
    AddPolygonCommand(vector<Figure*>* f);

    void exec() override;
    string intro() override;
};

class AddRectangleCommand : public ICommand {
public:
    AddRectangleCommand(vector<Figure*>* f);

    void exec() override;
    string intro() override;
};

class AddTriangleCommand : public ICommand {
    void setTriangleCorner(Triangle* f, string corner);
public:
    AddTriangleCommand(vector<Figure*>* f);

    void exec() override;
    string intro() override;
};

#endif //ADDFIGURE_H
