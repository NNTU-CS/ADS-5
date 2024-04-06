// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
int isPriority(char operation) {
    if (operation == '*' || operation == '/') {
        return 2;
    } else if (operation == '+' || operation == '-') {
        return 1;
    } else {
        return 0;
    }
}
std::string infx2pstfx(const std::string inf) {
    std::string apostf = "";
    TStack<char, 100> stack1;
    for (int i = 0; i < inf.size(); i++) {
        char c = inf[i];
        if (isdigit(c)) {
            int operand = 0;
            while (i < inf.size() && isdigit(inf[i])) {
                operand = operand * 10 + (inf[i] - '0');
                i++;
            }
            i--;
            apostf += std::to_string(operand) + " ";
        } else if (isalpha(c)) {
            apostf += c;
            apostf += " ";
        } else if (c == '(') {
            stack1.push(c);
        } else if (c == ')') {
            while (!stack1.isEmpty() && stack1.watch() != '(') {
                apostf += stack1.pop();
                apostf += ' ';
            }
            if (!stack1.isEmpty() && stack1.watch() == '(') {
                stack1.pop();
            }
        } else if (isOperator(c)) {
            while (!stack1.isEmpty() &&
                   isPriority(stack1.watch()) >= isPriority(c)) {
                apostf += stack1.pop();
                apostf += ' ';
            }
            stack1.push(c);
        }
    }

    while (!stack1.isEmpty()) {
        apostf += stack1.pop();
        apostf += ' ';
    }
    if (!postf.empty() && apostf[apostf.size() - 1] == ' ') {
        apostf.pop_back();
    }

    return apostf;
}
int eval(const std::string pref) {
    TStack<int, 100> stack2;
    for (int i = 0; i < pref.size(); i++) {
        if (isdigit(pref[i])) {
            int aoperand = 0;
            while (i < pref.size() && isdigit(pref[i])) {
                aoperand = aoperand * 10 + (pref[i] - '0');
                i++;
            }
            i--;
            stack2.push(aoperand);
        } else if (isOperator(pref[i])) {
            int aoperand2 = stack2.pop();
            int aoperand1 = stack2.pop();
            if (pref[i] == '+') {
                stack2.push(aoperand1 + aoperand2);
            } else if (pref[i] == '-') {
                stack2.push(aoperand1 - aoperand2);
            } else if (pref[i] == '*') {
                stack2.push(aoperand1 * aoperand2);
            } else if (pref[i] == '/') {
                stack2.push(aoperand1 / aoperand2);
            }
        }
    }
    return stack2.pop();
}
