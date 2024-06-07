// Copyright 2021 NNTU-CS
#include <string>
#include <cctype>
#include <map>
#include "tstack.h"

int getPriority(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return -1;
    }
}

std::string infx2pstfx(std::string inf) {
    TStack<char> stack;
    std::string post;
    for (char c : inf) {
        if (std::isdigit(c)) {
            post += c;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                post += ' ';
                post += stack.pop();
            }
            stack.pop();
        } else {
            while (!stack.isEmpty() &&
                    getPriority(c) <= getPriority(stack.peek())) {
                post += ' ';
                post += stack.pop();
            }
            post += ' ';
            stack.push(c);
        }
    }
    while (!stack.isEmpty()) {
        post += ' ';
        post += stack.pop();
    }
    return post;
}

int eval(std::string post) {
    TStack<int> stack;
    int i = 0;
    while (i < post.length()) {
        if (post[i] == ' ') {
            i++;
            continue;
        }
        if (std::isdigit(post[i])) {
            int value = 0;
            while (i < post.length() && std::isdigit(post[i])) {
                value = value * 10 + (post[i++] - '0');
            }
            if (!stack.push(value)) {
                return -1;
            }
        } else {
            int right = stack.pop();
            int left = stack.pop();
            if (right == int() || left == int()) {
                return -1;
            }
            switch (post[i]) {
                case '+': stack.push(left + right); break;
                case '-': stack.push(left - right); break;
                case '*': stack.push(left * right); break;
                case '/': stack.push(left / right); break;
            }
            i++;
        }
    }
    return stack.pop();
}
