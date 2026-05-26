#ifndef OOP3_COMMAND_H
#define OOP3_COMMAND_H

#include "index.h"
#include "../calculator/calculator.h"

class NormalizeInputCommand : public ICommand {
    Calculator& calculator;
    std::string& input;

public:
    explicit NormalizeInputCommand(Calculator& _calculator, std::string& _input) :
        calculator(_calculator), input(_input) {};

    void exec() override;
};

class GetPostfixCommand : public ICommand {
    std::string &input, &output;

    int getPriority(char operation);
    std::string getPostfix(std::string& input);
    void clearRest(std::stack<std::string>& stackOperation, std::string& result);
    void closeParenthesis(std::stack<std::string>& stackOperation, std::string& result);

public:
    explicit GetPostfixCommand(std::string& _input, std::string& _output) : input(_input), output(_output) {};

    void exec() override;
};

class NormalizeOutputCommand : public ICommand {
    Calculator& calculator;
    std::string& output;

public:
    explicit NormalizeOutputCommand(Calculator& _calculator, std::string& _output) :
        calculator(_calculator), output(_output) {};

    void exec() override;
};

class CalculateCommand : public ICommand {
    Calculator& calculator;
    std::string& output;

public:
    explicit CalculateCommand(Calculator& _calculator, std::string& _output) :
        calculator(_calculator), output(_output) {};

    void exec() override;
};

#endif //OOP3_COMMAND_H
