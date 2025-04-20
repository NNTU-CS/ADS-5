// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <stack>
#include <cctype>
#include <algorithm>
#include "tstack.h"

static int getPrecedence(char oper) {
    return (oper == '+' || oper == '-') ? 1 :
           (oper == '*' || oper == '/') ? 2 : 0;
}

static bool isMathOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

std::string infx2pstfx(const std::string& infixExpr) {
    std::stack<char> operatorStack;
    std::string postfixExpr;

    for (size_t idx = 0; idx < infixExpr.size(); ++idx) {
        char currentChar = infixExpr[idx];

        if (std::isdigit(currentChar)) {
            std::string number;
            while (idx < infixExpr.size() &&
                   std::isdigit(infixExpr[idx])) {
                number.push_back(infixExpr[idx++]);
            }
            --idx;
            postfixExpr += number;
            postfixExpr.push_back(' ');
        }
        else if (currentChar == '(') {
            operatorStack.push(currentChar);
        }
        else if (currentChar == ')') {
            while (!operatorStack.empty() &&
                   operatorStack.top() != '(') {
                postfixExpr.push_back(operatorStack.top());
                postfixExpr.push_back(' ');
                operatorStack.pop();
            }
            if (!operatorStack.empty()) {
                operatorStack.pop(); // удалить '('
            }
        }
        else if (isMathOperator(currentChar)) {
            while (!operatorStack.empty() &&
                   isMathOperator(operatorStack.top()) &&
                   getPrecedence(operatorStack.top()) >=
                   getPrecedence(currentChar)) {
                postfixExpr.push_back(operatorStack.top());
                postfixExpr.push_back(' ');
                operatorStack.pop();
            }
            operatorStack.push(currentChar);
        }
    }

    while (!operatorStack.empty()) {
        if (operatorStack.top() != '(') {
            postfixExpr.push_back(operatorStack.top());
            postfixExpr.push_back(' ');
        }
        operatorStack.pop();
    }

    if (!postfixExpr.empty() && postfixExpr.back() == ' ') {
        postfixExpr.pop_back();
    }

    return postfixExpr;
}

int eval(const std::string& postfixExpr) {
    std::stack<int> valueStack;
    std::istringstream exprStream(postfixExpr);
    std::string token;

    while (exprStream >> token) {
        if (token.size() == 1 && isMathOperator(token[0])) {
            int rightOperand = valueStack.top();
            valueStack.pop();
            int leftOperand = valueStack.top();
            valueStack.pop();

            char op = token[0];
            int result = 0;

            if (op == '+') result = leftOperand + rightOperand;
            else if (op == '-') result = leftOperand - rightOperand;
            else if (op == '*') result = leftOperand * rightOperand;
            else if (op == '/') result = leftOperand / rightOperand;

            valueStack.push(result);
        }
        else {
            valueStack.push(std::stoi(token));
        }
    }

    return valueStack.top();
}
