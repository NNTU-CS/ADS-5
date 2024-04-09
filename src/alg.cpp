// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::string exit;
    for (char i : inf) {
        if (i == '(') {
            stack1.push(i);
        } else if (i >= '0' && i <= '9') {
            exit += i;
            exit += ' ';
        } else if (i == ')') {
            while (stack1.get() != '(' && !stack1.isEmpty()) {
                exit += stack1.pop();
                exit += ' ';
            }
            if (stack1.get() == '(')
                stack1.pop();
        } else if (i == '+' || i == '-' || i == '*' || i == '/') {
            while (!stack1.isEmpty() && (stack1.get() == '*' ||
                stack1.get() == '/' || (i == '+' || i == '-') &&
                (stack1.get() == '+' || stack1.get() == '-'))) {
                exit += stack1.pop();
                exit += ' ';
            }
            stack1.push(i);
        }
    }
    while (!stack1.isEmpty()) {
        exit += stack1.pop();
        exit += ' ';
    }
    exit.pop_back();
    return exit;
}

int eval(std::string pref) {
    TStack<int, 100> stack2;
    std::string sTemp;
    for (char i : pref) {
        if ((i >= '0' && i <= '9')) {
            sTemp += i;
        } else if (i == ' ' && !sTemp.empty()) {
            stack2.push(std::stoi(sTemp));
            sTemp.clear();
        } else if (i == '+' || i == '-' || i == '*' || i == '/') {
            switch (i) {
                case '*': {
                    int cTemp = stack2.pop();
                    stack2.push(stack2.pop() * cTemp);
                    break;
                }
                case '/': {
                    int cTemp = stack2.pop();
                    stack2.push(stack2.pop() / cTemp);
                    break;
                }
                case '+': {
                    int cTemp = stack2.pop();
                    stack2.push(stack2.pop() + cTemp);
                    break;
                }
                case '-': {
                    int cTemp = stack2.pop();
                    stack2.push(stack2.pop() - cTemp);
                    break;
                }
            }
        }
    }
    return stack2.pop();
}
