// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    std::string postfix;
    TStack<char, 100> stack;
    bool needsSpace = false;

    for (size_t i = 0; i < inf.length(); ++i) {
        if (isspace(inf[i])) continue;

        if (isdigit(inf[i])) {
            if (needsSpace) {
                postfix += ' ';
                needsSpace = false;
            }
            while (i < inf.length() && isdigit(inf[i])) {
                postfix += inf[i++];
            }
            i--;
            needsSpace = true;
        } else if (inf[i] == '(') {
            stack.push(inf[i]);
        } else if (inf[i] == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                if (needsSpace) {
                    postfix += ' ';
                    needsSpace = false;
                }
                postfix += stack.top();
                stack.pop();
                needsSpace = true;
            }
            if (!stack.isEmpty() && stack.top() == '(') {
                stack.pop();
            }
        } else {
            while (!stack.isEmpty() && stack.top() != '(' && 
                   precedence(inf[i]) <= precedence(stack.top())) {
                if (needsSpace) {
                    postfix += ' ';
                    needsSpace = false;
                }
                postfix += stack.top();
                stack.pop();
                needsSpace = true;
            }
            stack.push(inf[i]);
        }
    }

    while (!stack.isEmpty()) {
        if (needsSpace) {
            postfix += ' ';
            needsSpace = false;
        }
        postfix += stack.top();
        stack.pop();
        needsSpace = true;
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
        if (isdigit(token[0])) {
            stack.push(std::stoi(token));
        } else {
            if (stack.isEmpty()) return 0;
            int right = stack.top(); stack.pop();
            if (stack.isEmpty()) return 0;
            int left = stack.top(); stack.pop();

            switch (token[0]) {
                case '+': stack.push(left + right); break;
                case '-': stack.push(left - right); break;
                case '*': stack.push(left * right); break;
                case '/': 
                    if (right == 0) return 0;
                    stack.push(left / right); 
                    break;
                default: return 0;
            }
        }
    }

    return stack.isEmpty() ? 0 : stack.top();
}
