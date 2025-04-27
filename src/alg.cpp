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
            stack.arr[++stack.top] = c;
        }
        else if (c == ')') {
            while (stack.top != -1 && stack.arr[stack.top] != '(') {
                out += stack.arr[stack.top--];
                out += ' ';
            }
            if (stack.top != -1) --stack.top; // убрать '('
        }
        else { // оператор + - * /
            while (stack.top != -1 && priority(stack.arr[stack.top]) >= priority(c)) {
                out += stack.arr[stack.top--];
                out += ' ';
            }
            stack.arr[++stack.top] = c;
        }
        ++i;
    }

    while (stack.top != -1) {
        out += stack.arr[stack.top--];
        out += ' ';
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
            stack.arr[++stack.top] = std::stoi(token);
        }
        else {
            int b = stack.arr[stack.top--];
            int a = stack.arr[stack.top--];
            if (token == "+") stack.arr[++stack.top] = a + b;
            else if (token == "-") stack.arr[++stack.top] = a - b;
            else if (token == "*") stack.arr[++stack.top] = a * b;
            else if (token == "/") stack.arr[++stack.top] = a / b;
        }
    }
    return stack.arr[stack.top];
}
