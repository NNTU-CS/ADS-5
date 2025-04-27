// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include <map>
#include "tstack.h"

int priority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}

std::string infx2pstfx(const std::string& inf) {
    char stack[100];
    int top = -1;
    std::string out;
    size_t i = 0;

    while (i < inf.length()) {
        char c = inf[i];

        if (std::isspace(c)) {
            ++i;
            continue;
        } else if (std::isdigit(c)) {
            while (i < inf.length() && std::isdigit(inf[i])) {
                out += inf[i++];
            }
            out += ' ';
            continue;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                out += stack[top--];
                out += ' ';
            }
            if (top >= 0) {
                --top; // убрать '('
            }
        } else { // оператор
            while (top >= 0 && priority(stack[top]) >= priority(c)) {
                out += stack[top--];
                out += ' ';
            }
            stack[++top] = c;
        }
        ++i;
    }

    while (top >= 0) {
        out += stack[top--];
        out += ' ';
    }

    if (!out.empty() && out.back() == ' ') {
        out.pop_back();
    }
    return out;
}

int eval(const std::string& post) {
    int stack[100];
    int top = -1;
    std::stringstream ss(post);
    std::string token;

    while (ss >> token) {
        if (std::isdigit(token[0])) {
            stack[++top] = std::stoi(token);
        } else {
            int b = stack[top--];
            int a = stack[top--];
            if (token == "+") {
                stack[++top] = a + b;
            } else if (token == "-") {
                stack[++top] = a - b;
            } else if (token == "*") {
                stack[++top] = a * b;
            } else if (token == "/") {
                stack[++top] = a / b;
            }
        }
    }

    if (top >= 0) {
        return stack[top];
    } else {
        return 0;
    }
}
