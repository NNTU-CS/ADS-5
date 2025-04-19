// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    std::string result;
    TStack<char, 100> stack;
    std::map<char, int> precedence = {
        {'*', 3}, {'/', 3}, {'+', 2}, {'-', 2}, {'(', 1}};

    for (char c : inf) {
        if (isdigit(c)) {
            result += c;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                result += ' ';
                result += stack.pop();
            }
            stack.pop();
        } else {
            if (!result.empty() && isdigit(result.back())) {
                result += ' ';
            }
            while (!stack.isEmpty() &&
                precedence[stack.top()] >=precedence[c]) {
                result += stack.pop();
                result += ' ';
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        result += ' ';
        result += stack.pop();
    }

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    int num = 0;
    bool readingNum = false;

    for (char c : post) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
            readingNum = true;
        } else if (c == ' ') {
            if (readingNum) {
                stack.push(num);
                num = 0;
                readingNum = false;
            }
        } else {
            int b = stack.pop();
            int a = stack.pop();
            switch (c) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
            }
        }
    }

    return stack.top();
}
