// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack;
    std::string pst;
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            pst += inf[i];
            pst += ' ';
        } else if (inf[i] == '(') {
            stack.push('(');
        } else if (inf[i] == ')') {
            while (!stack.isempty() && stack.get() != '(') {
                pst += stack.get();
                pst += ' ';
                stack.pop();
            }
            if (!stack.isempty()) {
                stack.pop();
            }
        } else {
            while (!stack.isempty() && stack.get() != '(' &&
            (inf[i] =='+' || stack.get() =='*' || stack.get() == '/')) {
                pst += stack.get();
                pst += ' ';
                stack.pop();
            }
            stack.push(inf[i]);
        }
    }
    while (!stack.isempty()) {
        pst += stack.get();
        pst += ' ';
        stack.pop();
    }
    if (!pst.empty()) {
        pst.erase(pst.size() - 1);
    }
    return pst;
  return std::string("");
}

int eval(std::string pref) {
  TStack<int, 100> stack;
    for (int i = 0; i < pref.length(); i++) {
        char ch = pref[i];
        if (isdigit(ch)) {
            stack.push(ch - '0');
        } else if (ch == '+' || ch == '-' || ch == '/' || ch == '*') {
            int oper2 = stack.pop();
            int oper1 = stack.pop();
            switch (ch) {
                case '+':
                    stack.push(oper1 + oper2);
                    break;
                case '-':
                    stack.push(oper1 - oper2);
                    break;
                case '*':
                    stack.push(oper1 * oper2);
                    break;
                case '/':
                    stack.push(oper1 / oper2);
                    break;
            }
        }
    }
    return stack.pop();
  return 0;
}
