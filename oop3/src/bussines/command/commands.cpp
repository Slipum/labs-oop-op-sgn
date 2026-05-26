#include "commands.h"

#include <sstream>

std::string GetPostfixCommand::getPostfix(std::string& input) {
    std::string result;
    std::stack<std::string> stackOperation;
    std::string buffer;
    std::stringstream ss(input);

    while (std::getline(ss, buffer, ' ')) {
        if (buffer.empty()) continue;

        if (isdigit(static_cast<unsigned char>(buffer[buffer.size() - 1]))) {
            result.append(buffer);
            result.append(" ");
        } else {
            if (buffer[0] == ')') closeParenthesis(stackOperation, result);
            else if (buffer[0] == '(') stackOperation.push(buffer);
            else {
                while (!stackOperation.empty() &&
                       stackOperation.top()[0] != '(' &&
                       getPriority(buffer[0]) <= getPriority(stackOperation.top()[0])) {
                    result.append(stackOperation.top());
                    result.append(" ");
                    stackOperation.pop();
                       }
                stackOperation.push(buffer);
            }
        }
    }
    clearRest(stackOperation, result);
    return result;
}
int GetPostfixCommand::getPriority(char operation) {
    switch (operation) {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    }
    return 0;
}
void GetPostfixCommand::closeParenthesis(std::stack<std::string>& stackOperation, std::string& result) {
    while (!stackOperation.empty() && stackOperation.top()[0] != '(') {
        result.append(stackOperation.top());
        result.append(" ");
        stackOperation.pop();
    }

    if (!stackOperation.empty() && stackOperation.top()[0] == '(')
        stackOperation.pop();
}
void GetPostfixCommand::clearRest(std::stack<std::string>& stackOperation, std::string& result) {
    while (!stackOperation.empty()) {
        if (stackOperation.top()[0] != '(') {
            result.append(stackOperation.top());
            result.append(" ");
        }
        stackOperation.pop();
    }
}

void GetPostfixCommand::exec() {
    output = getPostfix(input);
}

void NormalizeInputCommand::exec() {
    calculator.normalizeInput(input);
}

void NormalizeOutputCommand::exec() {
    calculator.normalizeOutput(output);
}

void CalculateCommand::exec() {
    output = calculator.calculate(output);
}
