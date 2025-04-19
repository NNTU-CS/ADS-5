// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include <sstream>
#include "tstack.h"

int getPriority(char op) {
    switch (op) {
        case '+': 
        case '-': return 1;
        case '*': 
        case '/': return 2;
        default: return 0;
    }
}

std::string infx2pstfx(const std::string& input) {
    std::string result;
    TStack<char, 100> opStack;

    for (size_t i = 0; i < input.size(); ++i) {
        char ch = input[i];

        if (ch == ' ') continue;

        if (isdigit(ch)) {
            while (i < input.size() && isdigit(input[i])) {
                result += input[i];
                ++i;
            }
            --i;
            result += ' ';
        } else if (ch == '(') {
            opStack.push(ch);
        } else if (ch == ')') {
            while (!opStack.isEmpty() && opStack.top() != '(') {
                result += opStack.top();
                result += ' ';
                opStack.pop();
            }
            if (!opStack.isEmpty() && opStack.top() == '(') {
                opStack.pop();
            } else {
                throw std::runtime_error("Mismatched parenthesis");
            }
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!opStack.isEmpty() && getPriority(opStack.top()) >= getPriority(ch)) {
                result += opStack.top();
                result += ' ';
                opStack.pop();
            }
            opStack.push(ch);
        } else {
            throw std::runtime_error(std::string("Invalid character: ") + ch);
        }
    }

    while (!opStack.isEmpty()) {
        char topOp = opStack.top();
        if (topOp == '(' || topOp == ')') {
            throw std::runtime_error("Mismatched parentheses in expression");
        }
        result += topOp;
        result += ' ';
        opStack.pop();
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

int eval(const std::string& postfix) {
    TStack<int, 100> valStack;
    std::istringstream stream(postfix);
    std::string token;

    while (stream >> token) {
        if (isdigit(token[0])) {
            valStack.push(std::stoi(token));
        } else if (token.length() == 1 &&
                   (token[0] == '+' || token[0] == '-' ||
                    token[0] == '*' || token[0] == '/')) {

            if (valStack.isEmpty()) {
                throw std::runtime_error("Not enough operands");
            }

            int right = valStack.top(); valStack.pop();
            if (valStack.isEmpty()) {
                throw std::runtime_error("Not enough operands");
            }

            int left = valStack.top(); valStack.pop();
            int outcome = 0;

            switch (token[0]) {
                case '+': outcome = left + right; break;
                case '-': outcome = left - right; break;
                case '*': outcome = left * right; break;
                case '/':
                    if (right == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    outcome = left / right; break;
                default:
                    throw std::runtime_error("Unknown operator");
            }

            valStack.push(outcome);
        } else {
            throw std::runtime_error("Unexpected token: " + token);
        }
    }

    if (valStack.isEmpty()) {
        throw std::runtime_error("No result found");
    }

    int finalResult = valStack.top();
    valStack.pop();

    if (!valStack.isEmpty()) {
        throw std::runtime_error("Too many operands left on the stack");
    }

    return finalResult;
}
