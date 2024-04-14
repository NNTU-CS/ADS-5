// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include "tstack.h"

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

std::string infx2pstfx(std::string inf) {
    TStack <char, 100> stack;
    std::stringstream postfix;

    for (char c : inf) {
        if (c == ' ')
            continue;
        if (isdigit(c)) {
            postfix << c;
            continue;
        }
        if (c == '(') {
            stack.push(c);
            continue;
        }
        if (c == ')') {
            while (!stack.isEmpty() && stack.get() != '(') {
                postfix << ' ' << stack.get();
                stack.pop();
            }
            stack.pop();
            continue;
        }
        if (c == '*' || c == '/' || c == '+' || c == '-') {
            postfix << ' ';
         while (!stack.isEmpty() && precedence(stack.get()) >= precedence(c)) {
                postfix << stack.get() << ' ';
                stack.pop();
            }
            stack.push(c);
            continue;
        }
    }

    while (!stack.isEmpty()) {
        postfix << ' ' << stack.get();
        stack.pop();
    }

    return postfix.str();
}

int eval(std::string post) {
    TStack <int, 100> stack;
    std::stringstream expression(post);
    std::string token;
    int operand1, operand2;

    while (expression >> token) {
        if (isdigit(token[0])) {
            stack.push(std::stoi(token));
        } else if (token[0] == '*' || token[0] == '/') {
            operand2 = stack.get();
            stack.pop();
            operand1 = stack.get();
            stack.pop();
            switch (token[0]) {
            case '*':
                stack.push(operand1 * operand2);
                break;
            case '/':
                stack.push(operand1 / operand2);
                break;
            }
        } else if (token[0] == '+' || token[0] == '-') {
            operand2 = stack.get();
            stack.pop();
            operand1 = stack.get();
            stack.pop();
            switch (token[0]) {
            case '+':
                stack.push(operand1 + operand2);
                break;
            case '-':
                stack.push(operand1 - operand2);
                break;
            }
        }
    }

    return stack.get();
}
