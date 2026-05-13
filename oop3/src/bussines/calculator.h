#ifndef OOP3_CALCULATOR_H
#define OOP3_CALCULATOR_H
#include <stack>
#include <string>

using Accuracy = double;
using StackNumbers = std::stack<Accuracy>;
using StackOperations = std::stack<char>;

class Calculator {
    std::string& input;
    std::string& output;
    std::string temp;

    Accuracy getElem(StackNumbers& stack);
    Accuracy getOperation(Accuracy a, Accuracy b, char operation);
    int getPriority(char operation);

    void normalizeInput();
    void normalizeOutput();
    void getPostfix();
    void calc();
public:
    Calculator(std::string& input, std::string& output);

    ~Calculator() = default;
};

#endif //OOP3_CALCULATOR_H
