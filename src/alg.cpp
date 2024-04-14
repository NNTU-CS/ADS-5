// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::string pst;
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            pst += inf[i];
            pst += ' ';
        } else if (inf[i] == '(') {
            stack1.push('(');
        } else if (inf[i] == ')') {
            while (!stack1.isempty() && stack1.get() != '(') {
                pst += stack1.get();
                pst += ' ';
                stack1.pop();
            }
            if (!stack1.isempty()) {
                stack1.pop();
            }
        } else {
            while (!stack1.isempty() && stack1.get() != '(' &&
            (inf[i] =='+' || stack1.get() =='*' || stack1.get() == '/')) {
                pst += stack1.get();
                pst += ' ';
                stack1.pop();
            }
            stack1.push(inf[i]);
        }
    }
    while (!stack1.isempty()) {
        pst += stack1.get();
        pst += ' ';
        stack1.pop();
    }
    if (!pst.empty()) {
        pst.erase(pst.size() - 1);
    }
    return pst;
}

int eval(std::string pref) {
    TStack<int, 100> stack2;
    for (int i = 0; i < pref.length(); i++) {
        char ch = pref[i];
        if (isdigit(ch)) {
            stack2.push(ch - '0');
        } else if (ch == '+' || ch == '-' || ch == '/' || ch == '*') {
            int operand2 = stack2.pop();
            int operand1 = stack2.pop();
            switch (ch) {
                case '+':
                    stack2.push(operand1 + operand2);
                    break;
                case '-':
                    stack2.push(operand1 - operand2);
                    break;
                case '*':
                    stack2.push(operand1 * operand2);
                    break;
                case '/':
                    stack2.push(operand1 / operand2);
                    break;
            }
        }
    }
    return stack2.pop();
}
