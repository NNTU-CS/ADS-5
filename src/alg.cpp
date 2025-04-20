// Copyright 2025 NNTU-CS
#include "alg.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    std::string postfix = "";
    TStack<char, 100> stack;

    for (size_t i = 0; i < inf.length(); ++i) {
        if (isspace(inf[i])) continue;

        if (isdigit(inf[i])) {
            std::string num_str;
            while (i < inf.length() && isdigit(inf[i])) {
                num_str += inf[i];
                i++;
            }
            i--;
            postfix += num_str + " ";
        } else if (inf[i] == '(') {
            stack.push(inf[i]);
        } else if (inf[i] == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                postfix += stack.top();
                postfix += " ";
                stack.pop();
            }
            stack.pop();
        } else {
            while (!stack.isEmpty() &&
                   precedence(inf[i]) <= precedence(stack.top())) {
                postfix += stack.top();
                postfix += " ";
                stack.pop();
            }
            stack.push(inf[i]);
        }
    }

    while (!stack.isEmpty()) {
        postfix += stack.top();
        postfix += " ";
        stack.pop();
    }

    return postfix;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::stringstream ss(post);
    std::string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            stack.push(std::stoi(token));
        } else {
            int operand2 = stack.top();
            stack.pop();
            if(stack.isEmpty()) return 0;
            int operand1 = stack.top();
            stack.pop();

            int result;
            if (token == "+") {
                result = operand1 + operand2;
            } else if (token == "-") {
                result = operand1 - operand2;
            } else if (token == "*") {
                result = operand1 * operand2;
            } else if (token == "/") {
                if (operand2 == 0) return 0;
                result = operand1 / operand2;
            } else {
                return 0;
            }

            stack.push(result);
        }
    }
    if (stack.isEmpty()) return 0;

    return stack.top();
}
