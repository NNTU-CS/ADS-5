// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include <stack>

int getPriority(char op) {
    if (op == '(' || op == ')') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return -1;
}

std::string infixToPostfix(std::string infix) {
    std::string postfix = "";
    std::stack<char> operators;

    for (char c : infix) {
        if (isdigit(c)) {
            postfix += c;
            postfix += ' ';
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && getPriority(operators.top()) >= getPriority(c)) {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        postfix += ' ';
        operators.pop();
    }

    return postfix;
}

int evaluatePostfix(std::string postfix) {
    std::stack<int> operands;

    for (char c : postfix) {
        if (isdigit(c)) {
            operands.push(c - '0');
        } else if (c != ' ') {
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();

            switch (c) {
                case '+':
                    operands.push(operand1 + operand2);
                    break;
                case '-':
                    operands.push(operand1 - operand2);
                    break;
                case '*':
                    operands.push(operand1 * operand2);
                    break;
                case '/':
                    operands.push(operand1 / operand2);
                    break;
            }
        }
    }

    return operands.top();
}

