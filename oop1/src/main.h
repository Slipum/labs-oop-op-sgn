#ifndef MAIN_H
#define MAIN_H

#include "commands/menu/menu.h"

class MainFacade {
    vector<Figure*>* figures;
public:
    MainFacade() { figures = new vector<Figure*>(); };

    void exec();
    void test();

    ~MainFacade() = default;
};

#endif //MAIN_H
