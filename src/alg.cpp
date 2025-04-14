// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "tstack.h"

int prioritet(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::ostringstream result;
    bool flag = false;
    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (std::isspace(c)) continue;
        if (std::isdigit(c)) {
            if (flag) {
                result << ' ';
            }
            while (i < inf.size() && std::isdigit(inf[i])) {
                result << inf[i++];
            }
            flag = true;
        }
        else if (c == '(') {
            stack.push(c);
            flag = false;
        }
        else if (c == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                result << ' ' << stack.pop();
            }
            if (stack.isEmpty()) {
                throw std::invalid_argument("Mismatched parentheses");
            }
            stack.pop(); // Удаляем '('
            flag = true;
        }
        else if (isOperator(c)) {
            while (!stack.isEmpty() && stack.peek() != '(' && prioritet(c) <= prioritet(stack.peek())) {
                result << ' ' << stack.pop();
            }
            stack.push(c);
            flag = true;
        }
        else {
            throw std::invalid_argument("Invalid character");
        }
    }
    while (!stack.isEmpty()) {
        if (stack.peek() == '(') {
            throw std::invalid_argument("Mismatched parentheses");
        }
        result << ' ' << stack.pop();
    }
    return result.str();
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;
    while (iss >> token) {
        if (std::isdigit(token[0])) {
            stack.push(std::stoi(token));
        }
        else if (isOperator(token[0]) && token.size() == 1) {
            if (stack.isEmpty()) throw std::invalid_argument("Not enough operands");
            int right = stack.pop();
            if (stack.isEmpty()) throw std::invalid_argument("Not enough operands");
            int left = stack.pop();
            switch (token[0]) {
                case '+': stack.push(left + right); break;
                case '-': stack.push(left - right); break;
                case '*': stack.push(left * right); break;
                case '/':
                    if (right == 0) throw std::runtime_error("Division by zero");
                    stack.push(left / right);
                    break;
            }
        }
        else {
            throw std::invalid_argument("Invalid token");
        }
    }
    if (stack.isEmpty()) throw std::invalid_argument("Empty expression");
    int result = stack.pop();
    if (!stack.isEmpty()) throw std::invalid_argument("Too many operands");
    return result;
}
