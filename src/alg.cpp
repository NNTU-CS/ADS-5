// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <map>
#include "tstack.h"

bool isOperation(const char c) {
    const std::string operations = "()+-*/";
    return operations.find(c) != std::string::npos;
}

bool isOperand(const char c) {
    return !isOperation(c);
}

int getPriority(char c) {
    switch (c) {
    case '(': return 0;
    case ')': return 1;
    case '+':
    case '-': return 2;
    case '*':
    case '/': return 3;
    default: return -1;
    }
}

std::string appendOperand(std::string* post, const std::string& operand) {
    if (operand.empty()) {
        return "";
    }
    if (!post->empty()) {
        post->append(" ");
    }
    post->append(operand);
    return "";
}

void appendOperation(std::string* post, TStack<char, 100>* stack) {
    if (stack->get() != '(') {
        if (!post->empty()) {
            post->append(" ");
        }
        post->append(std::string(1, stack->get()));
    }
    stack->pop();
}

int calculate(int a, char o, int b) {
    switch (o) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: std::cout << "unkown operation: " << o << std::endl;
        exit(-1);
    }
}

std::string infx2pstfx(std::string inf) {
    std::string post = "";
    std::string operand = "";
    TStack<char, 100> stack;
    for (auto c : inf) {
        if (isOperand(c)) {
            operand += c;
            continue;
        }
        operand = appendOperand(&post, operand);
        int priority;
        priority = getPriority(c);
        if (priority == 0 || stack.isEmpty() ||
            priority > getPriority(stack.get())) {
        } else {
            while (!stack.isEmpty() && getPriority(stack.get()) >= priority) {
                appendOperation(&post, &stack);
            }
            if (stack.get() == '(') {
                stack.pop();
            }
        }
        if (c != ')') {
            stack.push(c);
        }
    }
    operand = appendOperand(&post, operand);
    while (!stack.isEmpty()) {
        appendOperation(&post, &stack);
    }
    return post;
}

int eval(std::string pref) {
    TStack<int, 100> stack;
    std::string s("");
    for (auto c : pref) {
        if (isOperation(c)) {
            int b = stack.get();
            stack.pop();
            int a = stack.get();
            stack.pop();
            int result = calculate(a, c, b);
            stack.push(result);
            continue;
        }
        if (c == ' ') {
            if (s.size() != 0) {
                int o = atoi(s.c_str());
                s.clear();
                stack.push(o);
            }
        } else {
            s += c;
        }
    }
    return stack.get();
}
