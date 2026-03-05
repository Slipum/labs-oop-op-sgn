#ifndef CHOICE_H
#define CHOICE_H

#include "logic.h"

#define ERROR 8

class Choices {
private:
    void printFigureTypes();

    void setNameFigure(Figure* f);

    bool setTriangleCorner(Triangle* f, string corner);

    void setPolygonCorner(vector<coord>* corners, string corner);

    void addRectangle(vector<Figure*>* figures);
    void addTriangle(vector<Figure*>* figures);
    void addPolygon(vector<Figure*>* figures);
    void addCircle(vector<Figure*>* figures);

    static bool compare(Figure* a, Figure* b) {
        return a->getArea() < b->getArea();
    };

    void deleteClass(vector<Figure*>* arr, int index);

    vector<int> getIndexes(vector<Figure*> figures, int area);
public:
    int addFigure(vector<Figure*>* figures);

    void printAllParams(vector<Figure*> figures);

    void printAllAreas(vector<Figure*> figures);

    void sumAreas(vector<Figure*> figures);

    void sortByArea(vector<Figure*>* figures);

    void deletePerNum(vector<Figure*>* figures);

    void deletePerArea(vector<Figure*>* figures);
};

class MenuCommand {
public:
    virtual void exec(vector<Figure*>* figures);
};

class AddFigureCommand : public MenuCommand {
public:
    void exec(vector<Figure*>* figures) override;
};




#endif //CHOICE_H
