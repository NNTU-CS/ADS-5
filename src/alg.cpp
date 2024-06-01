// Copyright 2021 NNTU-CS
#include <cstring>
#include <map>
#include "tstack.h"

TStack<char, 100> stack1;
TStack<int, 100> stack2;

int getPriority(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return -1;
    }
}

std::string infx2pstfx(std::string inf) {
    std::string res = "";
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] == '(') {
            stack1.push(inf[i]);
        } else if (inf[i] == ')') {
            while (!stack1.isEmpty() && stack1.top() != '(') {
                res += stack1.pop();
                res += " ";
            }
            stack1.pop();
        } else if (inf[i] >= '0' && inf[i] <= '9') {
            while (i < inf.length() && (inf[i] >= '0' && inf[i] <= '9')) {
                res += inf[i];
                i++;
            }
            res += " ";
            i--;
        } else if (strchr("+-*/^", inf[i])) {
            char op = inf[i];
            while (!stack1.isEmpty() &&
                getPriority(stack1.top()) >= getPriority(op)) {
                res += stack1.pop();
                res += " ";
            }
            stack1.push(op);
        }
    }
    while (!stack1.isEmpty()) {
        res += stack1.pop();
        res += " ";
    }
    return res.substr(0, res.length()-1);
}

int eval(std::string pref) {
    std::string number = "";
    for (int i = 0; i < pref.length(); i++) {
        if (pref[i] >= '0' && pref[i] <= '9') {
            number += pref[i];
        } else if (pref[i] == ' ') {
            if (number != "") {
                stack2.push(std::stoi(number));
                number = "";
            }
        } else if (pref[i] == '+' || pref[i] == '-'
            || pref[i] == '*' || pref[i] == '/') {
            int right = stack2.pop();
            int left = stack2.pop();
            switch (pref[i]) {
                case '*': {
                        stack2.push(left * right);
                        break;
                    }
                case '/': {
                        stack2.push(left / right);
                        break;
                    }
                case '+': {
                        stack2.push(left + right);
                        break;
                    }
                case '-': {
                        stack2.push(left - right);
                        break;
                    }
            }
        }
    }
    return stack2.pop();
}
