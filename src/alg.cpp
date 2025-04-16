// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <sstream>
#include "tstack.h"

int priorityLevel(char symbol) {
    switch (symbol) {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default: return 0;
    }
}

std::string infx2pstfx(const std::string& inf) {
    std::string resultStr;
    TStack<char, 100> operatorStack;
    for (size_t idx = 0; idx < inf.length(); idx++) {
        char currentChar = inf[idx];
        if (currentChar == ' ') {
            continue;
        }
        if (std::isdigit(currentChar)) {
            while (idx < inf.length() && std::isdigit(inf[idx])) {
                resultStr.push_back(inf[idx]);
                idx++;
            }
            idx--;
            resultStr.push_back(' ');
        } else if (currentChar == '(') {
            operatorStack.push(currentChar);
        } else if (currentChar == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                resultStr.push_back(operatorStack.top());
                resultStr.push_back(' ');
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == '(') {
                operatorStack.pop();
            } else {
                throw std::runtime_error("Invalid expression detected");
            }
        } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            while (!operatorStack.empty()
                && priorityLevel(operatorStack.top()) >= priorityLevel(currentChar)) {
                resultStr.push_back(operatorStack.top());
                resultStr.push_back(' ');
                operatorStack.pop();
            }
            operatorStack.push(currentChar);
        } else {
            throw std::runtime_error(std::string("Unrecognized character: ") + currentChar);
        }
    }
    while (!operatorStack.empty()) {
        if (operatorStack.top() == '(' || operatorStack.top() == ')') {
            throw std::runtime_error("Malformed expression");
        }
        resultStr.push_back(operatorStack.top());
        resultStr.push_back(' ');
        operatorStack.pop();
    }
    if (!resultStr.empty() && resultStr.back() == ' ') {
        resultStr.pop_back();
    }
    return resultStr;
}

int eval(const std::string& pref) {
    TStack<int, 100> valueStack;
    std::istringstream stream(pref);
    std::string element;
    while (stream >> element) {
        if (std::isdigit(element[0])) {
            int value = std::stoi(element);
            valueStack.push(value);
        } else if (element.length() == 1 && (element[0] == '+' || element[0] == '-'
            || element[0] == '*' || element[0] == '/')) {
            if (valueStack.empty()) {
                throw std::runtime_error("Insufficient operands for operation");
            }
            int secondOperand = valueStack.top();
            valueStack.pop();
            if (valueStack.empty()) {
                throw std::runtime_error("Insufficient operands for operation");
            }
            int firstOperand = valueStack.top();
            valueStack.pop();
            int computationResult = 0;
            switch (element[0]) {
                case '+': computationResult = firstOperand + secondOperand; break;
                case '-': computationResult = firstOperand - secondOperand; break;
                case '*': computationResult = firstOperand * secondOperand; break;
                case '/':
                    if (secondOperand == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    computationResult = firstOperand / secondOperand;
                    break;
                default:
                    throw std::runtime_error("Invalid operator");
            }
            valueStack.push(computationResult);
        } else {
            throw std::runtime_error("Invalid element in expression: " + element);
        }
    }
    if (valueStack.empty()) {
        throw std::runtime_error("No result in stack");
    }
    int finalValue = valueStack.top();
    valueStack.pop();
    if (!valueStack.empty()) {
        throw std::runtime_error("Expression has extra operands");
    }
    return finalValue;
}
