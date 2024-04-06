// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isOperator(char op) {
    return (op == '+' || op == '-' || op == '(' ||
        op == ')' || op == '/' || op == '*');
}
bool isDigit(char n) {
    return (n >= '0' && n <= '9');
}

int whatPrioritet(char op) {
    if (op == '-' || op == '+')
        return 1;
    if (op == '/' || op == '*')
        return 2;
    return 0;
}

std::string infx2pstfx(std::string inf) {
    std::string post;
    int c = 0;
    TStack <char, 100> stack1;
    for (char s : inf) {
        if (isDigit(s)) {
            c++;
            if (c == 1) {
                post += s;
                continue;
            }
            post = post + ' ' + s;
        } else if (isOperator(s)) {
            if (s == '(') {
                stack1.push(s);
            } else if (stack1.checkEmpty()) {
                stack1.push(s);
            } else if (whatPrioritet(s) > whatPrioritet(stack1.get())) {
                stack1.push(s);
            } else if (s == ')') {
                while (stack1.get() != '(') {
                    post = post + ' ' + stack1.get();
                    stack1.pop();
                }
                stack1.pop();
            } else {
                int x = whatPrioritet(s);
                int y = whatPrioritet(stack1.get());
                while (!stack1.checkEmpty() && x <= y) {
                    post = post + ' ' + stack1.get();
                    stack1.pop();
                }
                stack1.push(s);
            }
        }
    }
    while (!stack1.checkEmpty()) {
        post = post + ' ' + stack1.get();
        stack1.pop();
    }
    return post;
}

int eval(std::string pref) {
    TStack <int, 100> stack2;
    for (char s : pref) {
        if (isDigit(s)) {
            stack2.push(s - '0');
        } else if (isOperator(s)) {
            int x = stack2.get();
            stack2.pop();
            int y = stack2.get();
            stack2.pop();
            switch (s) {
            case '+':
                stack2.push(x + y);
                break;
            case '-':
                stack2.push(y - x);
                break;
            case '*':
                stack2.push(x * y);
                break;
            case '/':
                stack2.push(y / x);
                break;
            default:
                continue;
            }
        } else {
            continue;
        }
    }
    return stack2.get();
}
