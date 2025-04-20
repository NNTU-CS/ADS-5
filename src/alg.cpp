// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
using namespace std;

std::string infx2pstfx(const std::string& inf) {
    std::string infix = inf;
    std::string postfix = "";
    TStack<char, 100> opStack;

    auto priority = [](char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
        };
    auto isOp = [](char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
        };
    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        }
        else if (c == '(') {
            if (!opStack.push(c)) return "Открытая скобка!";
        }
        else if (c == ')') {
            while (!opStack.isEmpty() && opStack.peek() != '(') {
                postfix += opStack.pop();
            }
            if (!opStack.isEmpty() && opStack.peek() == '(') {
                opStack.pop();
            }
        }
        else if (isOp(c)) {
            while (!opStack.isEmpty() && priority(c) <= priority(opStack.peek())) {
                postfix += opStack.pop();
            }
        }
    }
    while (!opStack.isEmpty()) {
        if (opStack.peek() == '(' || opStack.peek() == ')') {
            return "Не хватает скобок!";
        }
        postfix += opStack.pop();
    }
    return postfix;
}

int eval(const std::string& post) {
    TStack<int, 100> numStack;

    for (char c : post) {
        if (isdigit(c)) {
            numStack.push(c - '0'); 
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            int operand2 = numStack.pop();
            int operand1 = numStack.pop();
            int result;
            if (c == '+') {
                result = operand1 + operand2;
            }
            else if (c == '-') {
                result = operand1 - operand2;
            }
            else if (c == '*') {
                result = operand1 * operand2;
            }
            else if (c == '/') {
                if (operand2 == 0) {
                    cout << "Вы делите на 0";
                    return 0;
                }
                result = operand1 / operand2;
            }
            numStack.push(result);
        }
    }
    if (!numStack.isEmpty()) {
        return numStack.pop();
    }
}
