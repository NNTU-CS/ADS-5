// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int Priorety(char digit) {
    if (digit == '*' || digit == '/') return 2;
    if (digit == '+' || digit == '-') return 1;
    return 0;
}

bool BoolOperator(char c) {
    return (c == '-' || c == '+' || c == '*' || c == '/');
}

std::string infx2pstfx(std::string inf) {
    std::string postfix;
    TStack<char, 100> stack1;
    for (char c : inf) {
        if (isdigit(c)) {
            postfix = postfix + c + ' ';
        } else if (c == '(') {
            stack1.push(c);
        } else if (BoolOperator(c)) {
            while (!stack1.IsEmptyy() && \
                Priorety(stack1.get()) >= Priorety(c)) {
                postfix = postfix + stack1.get() + ' ';
                stack1.pop();
            }
            stack1.push(c);
        } else if (c == ')') {
            while (!stack1.IsEmptyy() && stack1.get() != '(') {
                postfix = postfix + stack1.get() + ' ';
                stack1.pop();
            }
            stack1.pop();
        }
    }
    while (!stack1.IsEmptyy()) {
        postfix = postfix + stack1.get() + ' ';
        stack1.pop();
    }
    if (!postfix.empty()) {
        postfix.pop_back();
    }
    return postfix;
}

int eval(std::string post) {
    TStack<int, 100> stack2;
    std::string Value;
    for (char c : post) {
        if (isdigit(c)) {
            Value += c;
        } else if (Value != "") {
            stack2.push(std::atoi(Value.c_str()));
            Value = "";
        }
        if (BoolOperator(c)) {
            int op2 = stack2.get();
            stack2.pop();
            int op1 = stack2.get();
            stack2.pop();
            switch (c) {
            case '*':
                stack2.push(op1 * op2);
                break;
            case '/':
                stack2.push(op1 / op2);
                break;
            case '+':
                stack2.push(op1 + op2);
                break;
            case '-':
                stack2.push(op1 - op2);
                break;
            }
        }
    }
    if (Value != "") {
        stack2.push(std::atoi(Value.c_str()));
    }
    return stack2.get();
}
