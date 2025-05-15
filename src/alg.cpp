// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <stack>
#include <cctype>
#include <algorithm>
#include "tstack.h"

static int operatorPrecedence(char op) {
    return (op == '+' || op == '-') ? 1
        : (op == '*' || op == '/') ? 2
        : 0;
}

static bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infixToPostfix(const std::string& infix) {
    std::stack<char> operatorStack;
    std::string output;
    for (size_t index = 0; index < infix.size(); ++index) {
        char currentChar = infix[index];
        if (std::isdigit(currentChar)) {
            std::string number;
            while (index < infix.size() && std::isdigit(infix[index])) {
                number.push_back(infix[index++]);
            }
            --index;
            output += number;
            output.push_back(' ');
        } else if (currentChar == '(') {
            operatorStack.push(currentChar);
        } else if (currentChar == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                output.push_back(operatorStack.top());
                output.push_back(' ');
                operatorStack.pop();
            }
            if (!operatorStack.empty()) operatorStack.pop();
        } else if (isOperator(currentChar)) {
            while (!operatorStack.empty() && isOperator(operatorStack.top()) &&
                operatorPrecedence(operatorStack.top()) >= operatorPrecedence(currentChar)) {
                output.push_back(operatorStack.top());
                output.push_back(' ');
                operatorStack.pop();
            }
            operatorStack.push(currentChar);
        }
    }
    while (!operatorStack.empty()) {
        if (operatorStack.top() != '(') {
            output.push_back(operatorStack.top());
            output.push_back(' ');
        }
        operatorStack.pop();
    }
    if (!output.empty() && output.back() == ' ')
        output.pop_back();
    return output;
}

int evaluatePostfix(const std::string& postfix) {
    std::stack<int> valueStack;
    std::istringstream inputStream(postfix);
    std::string token;
    while (inputStream >> token) {
        if (token.size() == 1 && isOperator(token[0])) {
            int secondOperand = valueStack.top(); valueStack.pop();
            int firstOperand = valueStack.top(); valueStack.pop();
            char operatorChar = token[0];
            int result = 0;
            if (operatorChar == '+') result = firstOperand + secondOperand;
            else if (operatorChar == '-') result = firstOperand - secondOperand;
            else if (operatorChar == '*') result = firstOperand * secondOperand;
            else if (operatorChar == '/') result = firstOperand / secondOperand;
            valueStack.push(result);
        } else {
            valueStack.push(std::stoi(token));
        }
    }
    return valueStack.top();
}

