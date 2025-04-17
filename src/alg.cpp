// Copyright 2025 NNTU-CS
#include "tstack.h"
#include "alg.h"
#include <string>
#include <cctype>
#include <sstream>
#include <map>

int prioritet(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> op_stack;
    std::string output;
    size_t i = 0;

    while (i < inf.size()) {
        char c = inf[i];

        if (std::isdigit(c)) {
            std::string number;
            while (i < inf.size() && std::isdigit(inf[i])) {
                number += inf[i];
                i++;
            }
            output += number + " ";
        } else if (c == '(') {
            op_stack.Push(c);
            i++;
        } else if (c == ')') {
            while (!op_stack.IsEmpty() && op_stack.Top() != '(') {
                output += op_stack.Pop() + " ";
            }
            op_stack.Pop();
            i++;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!op_stack.IsEmpty() && op_stack.Top() != '(' && prioritet(c) <= prioritet(op_stack.Top())) {
                output += op_stack.Pop() + " ";
            }
            op_stack.Push(c);
            i++;
        } else {
            i++;
        }
    }

    while (!op_stack.IsEmpty()) {
        output += op_stack.Pop() + " ";
    }

    if (!output.empty()) {
        output.pop_back();
    }
    return output;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = stack.Pop();
            int a = stack.Pop();
            if (token == "+") {
                stack.Push(a + b);
            } else if (token == "-") {
                stack.Push(a - b);
            } else if (token == "*") {
                stack.Push(a * b);
            } else {
                stack.Push(a / b);
            }
        } else {
            stack.Push(std::stoi(token));
        }
    }

    return stack.Pop();
}
