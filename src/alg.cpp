// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int Pr(char iop) {
    switch (iop) {
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
    TStack<char, 100> ownStack;
    std::string res = "";
    for (int i = 0; i < inf.size(); i++) {
        if (isdigit(inf[i]) != 0) {
            res += inf[i];
        } else if (Pr(inf[i]) == 2 || Pr(inf[i]) == 3) {
            res += " ";
            if (ownStack.isEmpty() || Pr(ownStack.get()) == 0 ||
                Pr(inf[i]) > Pr(ownStack.get())) {
                ownStack.push(inf[i]);
            } else if (Pr(inf[i]) <= Pr(ownStack.get())) {
                while (Pr(inf[i]) <= Pr(ownStack.get())) {
                    res += ownStack.pop();
                    res += " ";
                }
                ownStack.push(inf[i]);
            }
        } else if (Pr(inf[i]) == 0) {
            ownStack.push(inf[i]);
        } else if (Pr(inf[i]) == 1) {
            while (Pr(ownStack.get()) != 0) {
                res += " ";
                res += ownStack.pop();
            }
            ownStack.pop();
        }
    }
    while (!ownStack.isEmpty()) {
        res += " ";
        res += ownStack.pop();
    }
    return std::string(res);
}
int calculate(const int a, const int b, const char oper) {
    switch (oper) {
    case '+':
        return b + a;
    case '-':
        return b - a;
    case '*':
        return a * b;
    case '/':
        return b / a;
    default:
        break;
    }
    return 0;
}

int eval(std::string pref) {
    TStack<int, 100> opStack2;
    for (int i = 0; i < pref.size(); i++) {
        if (isdigit(pref[i]) != 0) {
            int num = pref[i] - '0';
            opStack2.push(num);
        } else if (Pr(pref[i]) == 2 || Pr(pref[i]) == 3) {
            int a = opStack2.pop();
            int b = opStack2.pop();
            opStack2.push(calculate(a, b, pref[i]));
        }
    }
    return opStack2.pop();
}
