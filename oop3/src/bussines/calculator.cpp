#include "calculator.h"

#include <iostream>
#include <ostream>
#include <stack>

#include <sstream>

Calculator::Calculator(std::string& input, std::string& output) : input(input), output(output) {
    try {
        temp = std::string();
        normalizeInput();
        getPostfix();
        calc();
        normalizeOutput();
    } catch (std::exception& e) {
        output = e.what();
    }
};

void Calculator::normalizeInput() {
    if (input.empty())
        throw std::runtime_error("Empty input");

    std::vector<char> str(input.begin(), input.end());

    for (size_t i = 0; i + 1 < str.size(); ++i) {
        if (str[i] == '-' && (i == 0 || std::string("(+-*/").find(str[i - 1]) != std::string::npos)) {
            if (i > 0 && str[i - 1] == '(') {
                str.insert(str.begin() + i, ' ');
                ++i;
            }
            continue;
        }

        if (str[i] == '.' || str[i + 1] == '.') continue;

        if ((std::isdigit(static_cast<unsigned char>(str[i])) != std::isdigit(static_cast<unsigned char>(str[i + 1]))) || (str[i + 1] == '(' || str[i] == ')')) {
            str.insert(str.begin() + i + 1, ' ');
            ++i;
        }
    }
    input.assign(str.begin(), str.end());
}

Accuracy Calculator::getElem(StackNumbers& stack) {
    if (stack.size() == 0)
        throw std::runtime_error("Invalid input");
    Accuracy a = stack.top();
    stack.pop();
    return a;
}

void Calculator::getPostfix() {
    std::stringstream ss(input);
    std::string segment;
    std::stack<std::string> stackOperation;
    while(std::getline(ss, segment, ' ')) {
        if (isdigit(segment[segment.size() - 1])) {
            temp.append(segment);
            temp.append(" ");
        } else {
            if (segment[0] == ')') {
                temp.append(stackOperation.top());
                temp.append(" ");
                stackOperation.pop();
            } else if (segment[0] != '(') {
                while (!stackOperation.empty() &&
                       getPriority(segment[0]) <= getPriority(stackOperation.top()[0])) {
                    temp.append(stackOperation.top());
                    temp.append(" ");
                    stackOperation.pop();
                }
                stackOperation.push(segment);
            }
        }
    }

    while (stackOperation.size()) {
        temp.append(stackOperation.top());
        temp.append(" ");
        stackOperation.pop();
    }
}

int Calculator::getPriority(char operation) {
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

Accuracy Calculator::getOperation(Accuracy a, Accuracy b, char operation) {
    switch (operation) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
}

void Calculator::normalizeOutput() {
    if (output.find('.') != std::string::npos) {
        size_t last_not_zero = output.find_last_not_of('0');
        if (last_not_zero != std::string::npos) {

            if (output[last_not_zero] == '.') {
                output.erase(last_not_zero);
            } else {
                output.erase(last_not_zero + 1);
            }
        }
    }
}

void Calculator::calc() {
    std::stack<Accuracy> stack;
    std::stringstream ss(temp);
    std::string segment;

    while(std::getline(ss, segment, ' ')) {
        if (isdigit(segment[segment.size() - 1]))
            stack.push(std::stod(segment));
        else {
            Accuracy b = getElem(stack);
            Accuracy a = getElem(stack);
            stack.push(getOperation(a, b, segment[0]));
        }
    }
    output = std::to_string(stack.top());
}