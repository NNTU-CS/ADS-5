// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool operation(char iChar) {
    return (iChar == '*' || iChar == '/' || iChar == '-' || iChar == '+');
}

int priority(char iOper) {
    if (iOper == '*' || iOper == '/') return 2;
    if (iOper == '+' || iOper == '-') return 1;
    return 0;
}

std::string infx2pstfx(const std::string inf) {
    std::string postf;
    TStack<char, 100> stack1;
    for (int i = 0; i < inf.size(); i++) {
        char iChar = inf[i];
        if (isdigit(iChar)) {
            int operand = 0;
            while (i < inf.size() && isdigit(inf[i])) {
                operand = operand * 10 + (inf[i] - '0');
                i++;
            }
            i--;
            postf += std::to_string(operand) + " ";
        } else if (isalpha(iChar)) {
            postf += iChar;
            postf += " ";
        } else if (iChar == '(') {
            stack1.push(iChar);
        } else if (iChar == ')') {
            while (!stack1.isEmpty() && stack1.watch() != '(') {
                postf += stack1.pop();
                postf += ' ';
            }
            if (!stack1.isEmpty() && stack1.watch() == '(') {
                stack1.pop();
            }
        } else if (operation(iChar)) {
            while (!stack1.isEmpty() &&
                   priority(stack1.watch()) >= priority(iChar)) {
                postf += stack1.pop();
                postf += ' ';
            }
            stack1.push(iChar);
        }
    }
    while (!stack1.isEmpty()) {
        postf += stack1.pop();
        postf += ' ';
    }
    if (!postf.empty()) {
        postf.pop_back();
    }
    return postf;
}

int eval(const std::string pref) {
    TStack<int, 100> stack2;
    for (int i = 0; i < pref.size(); i++) {
        if (isdigit(pref[i])) {
            int operand = 0;
            while (i < pref.size() && isdigit(pref[i])) {
                operand = operand * 10 + (pref[i] - '0');
                i++;
            }
            i--;
            stack2.push(operand);
        } else if (operation(pref[i])) {
            int iOper2 = stack2.pop();
            int iOper1 = stack2.pop();
            if (pref[i] == '+') {
                stack2.push(iOper1 + iOper2);
            } else if (pref[i] == '-') {
                stack2.push(iOper1 - iOper2);
            } else if (pref[i] == '*') {
                stack2.push(iOper1 * iOper2);
            } else if (pref[i] == '/') {
                stack2.push(iOper1 / iOper2);
            }
        }
    }
    return stack2.pop();
}
