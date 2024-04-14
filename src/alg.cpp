// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int priority(char ch) {
    if (ch == '*' || ch == '/') {
        return 2;
    }
    if (ch == '+' || ch == '-') {
        return 1;
    }
    return 0;
}

bool isOperator(char x) {
    return x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')';
}

std::string infx2pstfx(std::string inf) {
    std::string postfix;
    int count = 0;
    Stack<char, 100> stack;
    for (int i = 0; i < inf.length(); i++) {
        if (isdigit(inf[i])) {
            count++;
            if (count == 1) {
                postfix += inf[i];
                continue;
            }
            postfix = postfix + ' ' + inf[i];
        } else if (isOperator(inf[i])) {
            if (inf[i] == '(') {
                stack.push(inf[i]);
            } else if (stack.isEmpty()) {
                stack.push(inf[i]);
            } else if (stack.get() == '(') {
                stack.push(inf[i]);
            } else if (priority(inf[i]) > priority(stack.get())) {
                stack.push(inf[i]);
            } else if (inf[i] == ')') {
                while (!stack.isEmpty() && stack.get() != '(') {
                    postfix = postfix + ' ' + stack.get();
                    stack.pop();
                }
                stack.pop();
            } else {
                while (!stack.isEmpty()) {
                    postfix = postfix + ' ' + stack.get();
                    stack.pop();
                }
                stack.push(inf[i]);
            }
        }
    }
    while (!stack.isEmpty()) {
        postfix = postfix + ' ' + stack.get();
        stack.pop();
    }
    return postfix;
}


int eval(std::string pref) {
    Stack<int, 100> stack;
    std::string number = "";
    for (int i = 0; i < pref.length(); i++) {
        if (pref[i] == ' ') {
            continue;
        }
        number += pref[i];
    }
    for (int i = 0; i < number.length(); i++) {
        int num = number[i];
        if (isdigit(num)) {
            stack.push(num -'0');
        } else if (isOperator(number[i])) {
            int n1 = stack.get();
            stack.pop();
            int n2 = stack.get();
            stack.pop();
            if (num == '+') {
                stack.push(n1 + n2);
            } else if (num == '-') {
                stack.push(n2 - n1);
            } else if (num == '*') {
                stack.push(n1 * n2);
            } else if (num == '/') {
                stack.push(n2 / n1);
            } else {
                continue;
            }
        } else {
            continue;
        }
    }
    return stack.get();
}
