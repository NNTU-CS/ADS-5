// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>
#include <map>
#include "tstack.h"
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
std::string infx2pstfx(const std::string& inf) {
    std::stack<char> stack;
    std::string result;
    std::istringstream iss(inf);
    std::string token;
    while (iss >> token) {
        if (isdigit(token[0])) {
            result += token + " ";
        } else if (token[0] == '(') {
            stack.push('(');
        } else if (token[0] == ')') {
            while (!stack.empty() && stack.top() != '(') {
                result += stack.top();
                result += " ";
                stack.pop();
            }
            stack.pop();
        } else {
            while (!stack.empty() && precedence(stack.top()) >= precedence(token[0])) {
                result += stack.top();
                result += " ";
                stack.pop();
            }
            stack.push(token[0]);
        }
    }
    while (!stack.empty()) {
        result += stack.top();
        result += " ";
        stack.pop();
    }

    return result;
}
int eval(const std::string& pref) {
    std::stack<int> stack;
    std::istringstream iss(pref);
    std::string token;
    while (iss >> token) {
        if (isdigit(token[0])) {
            stack.push(std::stoi(token));
        } else {
            int right = stack.top(); stack.pop();
            int left = stack.top(); stack.pop();
            switch (token[0]) {
                case '+':
                    stack.push(left + right);
                    break;
                case '-':
                    stack.push(left - right);
                    break;
                case '*':
                    stack.push(left * right);
                    break;
                case '/':
                    stack.push(left / right);
                    break;
            }
        }
    }
    return stack.top();
}
