// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char x) {
    switch (x) {
        case '(': return 0;
        case ')': return 1;
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 3;
        default: return -1;
    }
}
std::string infx2pstfx(std::string inf) {
    std::string num_str, num1_str;
    TStack<char, 100> stack1;
    for (auto& x : inf) {
        int pr = prior(x);
        if (pr == -1) {
            num_str = num_str + x + ' ';
        } else {
            char zna = stack1.get();
            if (pr == 0 || prior(zna) < pr && stack1.isEmpty() || x == ')') {
                if (x == ')') {
                    while (prior(zna) >= pr) {
                        num_str = num_str + zna + ' ';
                        stack1.pop();
                        if (!stack1.isEmpty()) {
                            zna = stack1.get();
                        } else {
                            break;
                        }
                    }
                    stack1.pop();
                } else {
                    stack1.push(x);
                }
            } else {
                while (prior(zna) >= pr) {
                    num_str = num_str + zna + ' ';
                    stack1.pop();

                    if (!stack1.isEmpty()) {
                        zna = stack1.get();
                    } else {
                        break;
                    }
                }
                stack1.push(x);
            }
        }
    }
    while (!stack1.isEmpty()) {
        num_str = num_str + stack1.get() + ' ';
        stack1.pop();
    }
    for (int i = 0; i < num_str.size() - 1; i++) {
        num1_str += num_str[i];
    }
    return num1_str;
}

int eval(std::string pref) {
    std::string num_str = "";
    TStack<int, 100> stack1;
    for (int i = 0; i < pref.size(); ++i) {
        if (prior(pref[i]) == -1) {
            if (pref[i] == ' ') {
                continue;
            } else if (isdigit(pref[i + 1])) {
                num_str += pref[i];
                continue;
            } else {
                num_str += pref[i];
                int value = atoi(num_str.c_str());
                stack1.push(value);
                num_str = "";
            }
        } else {
            int b = stack1.pop();
            int a = stack1.pop();
            if (pref[i] == '+') {
                stack1.push(a + b);
            } else if (pref[i] == '-') {
                stack1.push(a - b);
            } else if (pref[i] == '*') {
                stack1.push(a * b);
            } else if (pref[i] == '/') {
                stack1.push(a / b);
            }
        }
    }
    return stack1.get();
}
