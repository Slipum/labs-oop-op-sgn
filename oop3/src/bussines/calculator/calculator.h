#ifndef OOP3_CALCULATOR_H
#define OOP3_CALCULATOR_H
#include <stack>
#include <string>

using Accuracy = double;
using StackNumbers = std::stack<Accuracy>;
using StackOperations = std::stack<char>;

class Calculator {
    Accuracy getElem(StackNumbers& stack);
    Accuracy getOperation(Accuracy a, Accuracy b, char operation);

    void normalizeNumbers(size_t& i, std::vector<char>& str);
    bool unaryMinus(size_t& i, std::vector<char>& str);
public:
    Calculator() = default;
    ~Calculator() = default;

    void normalizeInput(std::string& input);
    std::string calculate(std::string input);
    void normalizeOutput(std::string& output);
};

#endif //OOP3_CALCULATOR_H
