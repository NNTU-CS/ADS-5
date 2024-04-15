// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int getPriority(char symbol) {
    switch (symbol) {
    case '(':
        return 0;
        break;
    case ')':
        return 1;
        break;
    case '+':
        return 2;
        break;
    case '-':
        return 2;
        break;
    case '*':
        return 3;
        break;
    case '/':
        return 3;
        break;
    default:
        return 0;
        break;
    }
}
std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::string result = "";
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            if (inf[i + 1] >= '0' && inf[i + 1] <= '9') {
                result += inf[i];
            } else {
                result += inf[i];
                result += ' ';
            }
        } else {
            if (inf[i] == '(') {
                stack1.push('(');
            } else if (inf[i] == ')') {
                while (!stack1.isEmpty() && stack1.get() != '(') {
                    result += stack1.get();
                    result += ' ';
                    stack1.pop();
                }
                if (!stack1.isEmpty()) {
                    stack1.pop();
                }
            } else {
                if (getPriority(inf[i]) > getPriority(stack1.get())) {
                    stack1.push(inf[i]);
                } else {
                    while (getPriority(inf[i]) <= getPriority(stack1.get())) {
                        result += stack1.get();
                        result += ' ';
                        stack1.pop();
                    }
                    stack1.push(inf[i]);
                }
            }
        }
    }
    while (!stack1.isEmpty()) {
        result += stack1.get();
        result += ' ';
        stack1.pop();
    }
    result.pop_back();
    return result;
}
int calculate(const int a, const int b, const char symbol) {
    switch (symbol) {
    case '+':
        return b + a;
        break;
    case '-':
        return b - a;
        break;
    case '*':
        return b * a;
        break;
    case '/':
        return b / a;
        break;
    default:
        return 0;
        break;
    }
}
int eval(std::string pref) {
    TStack<int, 100> stack2;
    int result = 0;
    std::string nums = "";
    for (int i = 0; i < pref.length(); i++) {
        if (pref[i] >= '0' && pref[i] <= '9') {
            if (pref[i + 1] >= '0' && pref[i + 1] <= '9') {
                nums += pref[i];
            } else {
                nums += pref[i];
                stack2.push(std::stoi(nums));
                nums = "";
            }
        } else if (pref[i] == ' ') {
            continue;
        } else {
            int a = stack2.get();
            stack2.pop();
            int b = stack2.get();
            stack2.pop();
            stack2.push(calculate(a, b, pref[i]));
        }
    }
    int res = stack2.get();
    stack2.pop();
    return res;
}
