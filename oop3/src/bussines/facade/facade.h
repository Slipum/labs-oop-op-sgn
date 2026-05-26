#ifndef OOP3_FACADE_H
#define OOP3_FACADE_H

#include "../calculator/calculator.h"

class CalcucateFacade {
    Calculator calculator;

public:
    void getCalculate(std::string& input, std::string& output);
};



#endif //OOP3_FACADE_H
