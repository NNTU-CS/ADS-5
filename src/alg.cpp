// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioryty_oper(char x) {
    switch (x) {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+': case '-':
        return 2;
    case '*': case '/':
        return 3;
    default:
        return -1;
    }
}
std::string infx2pstfx(std::string inf) {
    std::string rez, rez1;
    TStack <char, 100> stack1;
    for (auto& x : inf) {
        int p = prioryty_oper(x);
        if (p == -1) {
            rez = rez + x + ' ';
        } else {
            char elem = stack1.get();
            if (p == 0 || prioryty_oper(elem) < p || stack1.isEmpty()) {
                stack1.push(x);
            } else {
                if (x == ')') {
                    while (prioryty_oper(elem) >= p) {
                        rez = rez + elem + ' ';
                        stack1.pop();
                        elem = stack1.get();
                    }
                    stack1.pop();
                } else {
                    while (prioryty_oper(elem) >= p) {
                        rez = rez + elem + ' ';
                        stack1.pop();
                        elem = stack1.get();
                    }
                    stack1.push(x);
                }
            }
        }
    }
    while (!stack1.isEmpty()) {
        rez = rez + stack1.get() + ' ';
        stack1.pop();
    }
    for (int i = 0; i < rez.size() - 1; i++)
        rez1 += rez[i];
    return rez1;
}

int eval(std::string post) {
    TStack<int, 100> stack1;
    std::string rez = "";
    for (int i = 0; i < post.size(); ++i) {
        if (prioryty_oper(post[i]) == -1) {
            if (post[i] == ' ') {
                continue;
            } else if (isdigit(post[i + 1])) {
                rez += post[i];
                    continue;
            } else {
                rez += post[i];
                stack1.push(atoi(rez.c_str()));
                rez = "";
            }
        } else {
            int b = stack1.get();
            stack1.pop();
            int a = stack1.get();
            stack1.pop();
            if (post[i] == '+')
                stack1.push(a + b);
            if (post[i] == '-')
                stack1.push(a - b);
            if (post[i] == '*')
                stack1.push(a * b);
            if (post[i] == '/')
                stack1.push(a / b);
        }
    }
    return stack1.get();
}
