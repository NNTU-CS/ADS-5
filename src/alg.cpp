// Copyright 2021 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string postfix;

    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (std::isspace(c)) continue;

        if (std::isdigit(c)) {
            std::string num;
            while (i < inf.size() && std::isdigit(inf[i])) {
                num += inf[i];
                ++i;
            }
            --i;
            postfix += num + ' ';
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                postfix += stack.pop();
                postfix += ' ';
            }
            stack.pop();
        } else if (isOperator(c)) {
            while (!stack.isEmpty() &&
                   precedence(stack.top()) >= precedence(c)) {
                postfix += stack.pop();
                postfix += ' ';
                   }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        postfix += stack.pop();
        postfix += ' ';
    }

    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0])) {
            stack.push(std::stoi(token));
        } else {
            int b = stack.pop();
            int a = stack.pop();
            stack.push(applyOp(a, b, token[0]));
        }
    }

    return stack.pop();
}
