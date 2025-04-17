// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include <sstream>
#include <map>
#include "tstack.h"

bool operIS(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int prioritet(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
int operOPER(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
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
            stack.Push(c);
        } else if (c == ')') {
            while (!stack.IsEmpty() && stack.Top() != '(') {
                postfix += stack.Pop();
                postfix += ' ';
            }
            stack.Pop();
        } else if (operIS(c)) {
            while (!stack.IsEmpty() && prioritet(stack.Top()) >= prioritet(c)) {
                postfix += stack.Pop();
                postfix += ' ';
            }
            stack.Push(c);
        }
    }

    while (!stack.IsEmpty()) {
        postfix += stack.Pop();
        postfix += ' ';
    }

    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0])) {
            stack.Push(std::stoi(token));
        } else {
            int b = stack.Pop();
            int a = stack.Pop();
            stack.Push(operOPER(a, b, token[0]));
        }
    }

    return stack.Pop();
}
