// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include <sstream>
#include "tstack.h"

int precedence(char oper) {
    switch (oper) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

std::string infx2pstfx(const std::string& expression) {
    std::string result;
    TStack<char, 100> operatorStack;

    for (size_t i = 0; i < expression.length(); ++i) {
        char current = expression[i];

        if (current == ' ') {
            continue;
        }

        if (std::isdigit(current)) {
            while (i < expression.length() && std::isdigit(expression[i])) {
                result.push_back(expression[i]);
                ++i;
            }
            --i;
            result.push_back(' ');
        } else if (current == '(') {
            operatorStack.push(current);
        } else if (current == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                result.push_back(operatorStack.top());
                result.push_back(' ');
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == '(') {
                operatorStack.pop();
            } else {
                throw std::runtime_error("Unmatched parenthesis");
            }
        } else if (current == '+'  current == '-'  current == '*' || current == '/') {
            while (!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(current)) {
                result.push_back(operatorStack.top());
                result.push_back(' ');
                operatorStack.pop();
            }
            operatorStack.push(current);
        } else {
            throw std::runtime_error(std::string("Invalid character: ") + current);
        }
    }

    while (!operatorStack.empty()) {
        if (operatorStack.top() == '(' || operatorStack.top() == ')') {
            throw std::runtime_error("Unmatched parenthesis in final stack");
        }
        result.push_back(operatorStack.top());
        result.push_back(' ');
        operatorStack.pop();
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

int eval(const std::string& postfixExpr) {
    TStack<int, 100> valueStack;
    std::istringstream tokenizer(postfixExpr);
    std::string token
