// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int Prioritet(char op) {
    switch (op) {
    case '(':
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return -1;
    }
}

std::string infx2pstfx(const std::string& infix) {
    if (infix.empty()) {
        throw "Is empty";
    }

    std::string postfix;
    TStack<char, 50> operators;

    for (size_t i = 0; i < infix.length(); ++i) {
        char ch = infix[i];

        if (isDigit(ch)) {
            std::string number;
            number += ch;

            while (i + 1 < infix.length() && isDigit(infix[i + 1])) {
                number += infix[++i];
            }

            postfix += number;
            postfix += ' ';
        }
        else if (ch == '(') {
            operators.Push(ch);
        }
        else if (ch == ')') {
            while (!operators.isEmpty() && operators.peekLast() != '(') {
                postfix += operators.pop();
                postfix += ' ';
            }
            if (!operators.isEmpty()) {
                operators.pop();
            }
        }
        else if (isOperator(ch)) {
            while (!operators.isEmpty() &&
                   Prioritet(ch) <= Prioritet(operators.peekLast())) {
                postfix += operators.pop();
                postfix += ' ';
            }
            operators.Push(ch);
        }
    }

    while (!operators.isEmpty()) {
        postfix += operators.pop();
        postfix += ' ';
    }

    if (!postfix.empty()) {
        postfix.pop_back();
    }

    return postfix;
}

int eval(const std::string& postfix) {
    TStack<int, 50> operands;

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];

        if (isDigit(ch)) {
            std::string number;
            number += ch;

            while (i + 1 < postfix.length() && isDigit(postfix[i + 1])) {
                number += postfix[++i];
            }

            operands.Push(std::stoi(number));
        }
        else if (isOperator(ch)) {
            int right = operands.pop();
            int left  = operands.pop();

            switch (ch) {
            case '+':
                operands.Push(left + right);
                break;
            case '-':
                operands.Push(left - right);
                break;
            case '*':
                operands.Push(left * right);
                break;
            case '/':
                operands.Push(left / right);
                break;
            }
        }
    }

    return operands.pop();
}
