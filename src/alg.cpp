// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

TStack<char, 100> stack1;
TStack<int, 100> stack2;

int prior(char operand) {
    if (operand == '-') return 1;
    if (operand == '+') return 1;
    if (operand == '*') return 2;
    if (operand == '/') return 2;
    return 0;
}

std::string infx2pstfx(std::string inf) {
    std::string post;
    TStack<char, 100> stack;

    for (char c : inf) {
        if (isdigit(c)) {
            post += c;
            post += ' ';
        } else if (c == '(') {
            stack.push(c);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.isEmpty() && prior(stack.see()) >= prior(c)) {
                post = post + stack.see() + ' ';
                stack.pop();
            }
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.see() != '(') {
                post = post + stack.see() + ' ';
                stack.pop();
            }
            stack.pop();
        }
    }
    while (!stack.isEmpty()) {
        post = post + stack.see() + ' ';
        stack.pop();
    }
    if (!post.empty()) {
        post.pop_back();
    }
    return post;
}

int eval(std::string pref) {
    std::string strNumber = "";
    for (char c : pref) {
        if (c != ' ' && c != '+' && c != '-' && c != '*' && c != '/') {
            strNumber += c;
        }
        if (c == ' ') {
            if (!strNumber.empty()) {
                int num = std::stoi(strNumber);
                stack2.push(num);
                strNumber = "";
            }
        }
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            int b = stack2.see();
            stack2.pop();
            int a = stack2.see();
            stack2.pop();

            if (c == '+') {
                stack2.push((a + b));
            } else if (c == '-') {
                stack2.push((a - b));
            } else if (c == '*') {
                stack2.push((a * b));
            } else if (c == '/') {
                stack2.push((a / b));
            }
        }
    }

    return stack2.see();
}
