// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
    std::map<char, int> priority;
    priority['+'] = 1;
    priority['-'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;

    std::string post;
    TStack<char, 100> stack;

    for (char c : inf) {
        if (isdigit(c)) {
            post += c;
            post += ' ';
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (stack.getTop() != '(') {
                post += stack.pop();
                post += ' ';
            }
            stack.pop();
        } else {
            while (!stack.isEmpty() &&
                   priority[c] <= priority[stack.getTop()]) {
                post += stack.pop();
                post += ' ';
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        post += stack.pop();
        post += ' ';
    }

    return post;
    return std::string("");
}

int eval(std::string pref) {
    TStack<int, 100> stack;

    for (char c : pref) {
        if (isdigit(c)) {
            stack.push(c - '0');
        } else if (c == ' ') {
            continue;
        } else {
            int b = stack.pop();
            int a = stack.pop();
            int result;

            switch (c) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
            }

            stack.push(result);
        }
    }

    return stack.pop();
    return 0;
}
