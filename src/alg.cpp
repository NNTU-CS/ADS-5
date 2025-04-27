// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include <map>
#include "tstack.h"

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string out;
    size_t i = 0;

    while (i < inf.length()) {
        char c = inf[i];

        if (std::isspace(c)) {
            ++i;
            continue;
        }
        if (std::isdigit(c)) {
            while (i < inf.length() && std::isdigit(inf[i])) {
                out += inf[i++];
            }
            out += ' ';
            continue;
        }
        if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                out += stack.top();
                out += ' ';
                stack.pop();
            }
            if (!stack.empty()) stack.pop();
        }
        else {
            while (!stack.empty() && priority(stack.top()) >= priority(c)) {
                out += stack.top();
                out += ' ';
                stack.pop();
            }
            stack.push(c);
        }
        ++i;
    }
    while (!stack.empty()) {
        out += stack.top();
        out += ' ';
        stack.pop();
    }
    if (!out.empty() && out.back() == ' ') {
        out.pop_back();
    }
    return out;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::stringstream ss(post);
    std::string token;

    while (ss >> token) {
        if (std::isdigit(token[0])) {
            stack.push(std::stoi(token));
        }
        else {
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            if (token == "+") stack.push(a + b);
            else if (token == "-") stack.push(a - b);
            else if (token == "*") stack.push(a * b);
            else if (token == "/") stack.push(a / b);
        }
    }
    return stack.top();
}
