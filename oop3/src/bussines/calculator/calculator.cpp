#include "calculator.h"

#include <iostream>
#include <ostream>
#include <stack>

#include <sstream>

void Calculator::normalizeInput(std::string& input) {
    if (input.empty()) throw std::runtime_error("Empty input");
    std::vector<char> str(input.begin(), input.end());

    if (str[0] == '.' && str.size() == 1) throw std::runtime_error("Invalid number format");

    int balance = 0;

    for (char c : str) {
        if (c == '(') ++balance;
        else if (c == ')') {
            --balance;
            if (balance < 0) throw std::runtime_error("Extra closing parenthesis");
        }
    }

    if (balance != 0) throw std::runtime_error("Mismatched parentheses");

    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '(') {
            size_t j = i + 1;
            while (j < str.size() && str[j] == ' ') j++;
            if (str[j] == ')') throw std::runtime_error("Empty parentheses");
        }

        if (unaryMinus(i, str)) continue;

        if (str[i] == '.') {
            if (i == 0 ||
                str[i - 1] == '(' ||
                std::string("+-*/").find(str[i - 1]) != std::string::npos) {

                str.insert(str.begin() + i, '0');
                ++i;
            }
        }

        normalizeNumbers(i, str);

        if (std::string("+-*/)").find(str[i]) != std::string::npos) {
            if (i > 0 && str[i - 1] != ' ') {
                str.insert(str.begin() + i, ' ');
                ++i;
            }
            if (i + 1 < str.size() && str[i + 1] != ' ')
                str.insert(str.begin() + i + 1, ' ');

            continue;
        }
    }

    input.assign(str.begin(), str.end());
}


bool Calculator::unaryMinus(size_t& i, std::vector<char>& str) {
    if (str[i] == '-' &&
            (i == 0 || std::string("(+-*/").find(str[i - 1]) != std::string::npos)) {
        if (i > 0 && str[i - 1] == '(') {
            str.insert(str.begin() + i, ' ');
            ++i;
        }

        if (i + 1 < str.size() && str[i + 1] == '(') {
            str.insert(str.begin() + i, '0');
            str.insert(str.begin() + i+1, ' ');
            ++i;
        }
        return true;
    }
    return false;
}

void Calculator::normalizeNumbers(size_t& i, std::vector<char>& str) {
    if (std::isdigit(static_cast<unsigned char>(str[i])) || str[i] == '.') {
        bool dotSeen = false;
        size_t j = i;

        while (j < str.size() &&
               (std::isdigit(static_cast<unsigned char>(str[j])) || str[j] == '.')) {
            if (str[j] == '.') {
                if (dotSeen) throw std::runtime_error("Invalid number format");
                dotSeen = true;
            }
            ++j;
        }

        if (!dotSeen) {
            str.insert(str.begin() + j, '.');
            str.insert(str.begin() + j + 1, '0');
            i = j + 1;
        } else {
            if (j > i && str[j - 1] == '.') {
                str.insert(str.begin() + j, '0');
                ++j;
            }
            i = j - 1;
        }
    }
}

Accuracy Calculator::getElem(StackNumbers& stack) {
    if (stack.size() == 0)
        throw std::runtime_error("Invalid input");
    Accuracy a = stack.top();
    stack.pop();
    return a;
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
            if (b == 0) throw std::runtime_error("Invalid input. Devision by zero.");
            return a / b;
    }
}

void Calculator::normalizeOutput(std::string& output) {
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

std::string Calculator::calculate(std::string input) {
    std::string output;

    std::stack<Accuracy> stack;
    std::stringstream ss(input);
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
    if (stack.size() == 0) throw std::runtime_error("Invalid input");
    output = std::to_string(stack.top());
    if (output.find("-0") != std::string::npos) {
        output = "0";
    }
    return output;
}