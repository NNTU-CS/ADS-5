// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include <stack>
#include "tstack.h"
int priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;}}

std::string infx2pstfx(const std::string& inf) {
    std::string postfix = "";
    TStack<char, 100> stack1;

    for (int i = 0; i < inf.length(); ++i) {
        char lnl = inf[i];
        if (isspace(lnl)) continue;
        if (isalnum(lnl)) {
            std::string numm;
            numm += lnl;
            size_t pos = i + 1;
            while (pos < inf.length() && isdigit(inf[pos])) {
                numm += inf[pos];
                pos++;
                i++;
            }
            postfix += numm + " ";
        } else if (lnl == '(') {
            stack1.Push(lnl);
        } else if (lnl == ')') {
            while (!stack1.IsEmpty() && stack1.peek() != '(') {
                postfix += stack1.Pop();
                postfix += " ";
            }
            if (!stack1.IsEmpty() && stack1.peek() == '(') {
                stack1.Pop();
            }
        } else {
            while (!stack1.IsEmpty() &&
                priority(lnl) <= priority(stack1.peek())) {
                postfix += stack1.Pop();
                postfix += " ";
            }
            stack1.Push(lnl);
        }
    }
    while (!stack1.IsEmpty()) {
        postfix += stack1.Pop();
        postfix += " ";
    }

    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }
    return postfix;
}

int eval(const std::string& pref) {
    TStack<int, 100> stack2;
    std::string numm;

    for (char lnl : pref) {
        if (isdigit(lnl)) {
            numm += lnl;
        } else if (isspace(lnl)) {
            if (numm.empty()) continue;
            stack2.Push(std::stoi(numm));
            numm = "";
        } else if (lnl == '+' || lnl == '-' || lnl == '*' || lnl == '/') {
            if (stack2.IsEmpty()) return 0;
            int operand2 = stack2.Pop();
             if (stack2.IsEmpty()) return 0;
            int operand1 = stack2.Pop();
            int result;

            switch (lnl) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                default: return 0;
            }
            stack2.Push(result);
        }
    }

    if (!stack2.IsEmpty()) {
        return stack2.Pop();
    } else {
        return 0;
    }
}
