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
    std::string postf = "";
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
            postf += std::to_string(operand) + " ";
        } else if (isalpha(c)) {
            postf += c;
            postf += " ";
        } else if (c == '(') {
            stack1.push(c);
        } else if (c == ')') {
            while (!stack1.isEmpty() && stack1.watch() != '(') {
                postf += stack1.pop();
                postf += ' ';
            }
            if (!stack1.isEmpty() && stack1.watch() == '(') {
                stack1.pop();
            }
        } else if (isOperator(c)) {
            while (!stack1.isEmpty() &&
                   isPriority(stack1.watch()) >= isPriority(c)) {
                postf += stack1.pop();
                postf += ' ';
            }
            stack1.push(c);
        }
    }

    while (!stack1.isEmpty()) {
        postf += stack1.pop();
        postf += ' ';
    }
    if (!postf.empty() && postf[postf.size() - 1] == ' ') {
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
        } else if (isOperator(pref[i])) {
            int operand2 = stack2.pop();
            int operand1 = stack2.pop();
            if (pref[i] == '+') {
                stack2.push(operand1 + operand2);
            } else if (pref[i] == '-') {
                stack2.push(operand1 - operand2);
            } else if (pref[i] == '*') {
                stack2.push(operand1 * operand2);
            } else if (pref[i] == '/') {
                stack2.push(operand1 / operand2);
            }
        }
    }

    return stack2.pop();
}
