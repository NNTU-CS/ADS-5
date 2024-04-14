// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::map<char, int> pr {
        {'(', 0}, {')', 1}, {'-', 2}, {'+', 2}, {'/', 3}, {'*', 3}
};

TStack<char, 100> stack0;
TStack<int, 100> stackend;

std::string infx2pstfx(std::string inf) {
    std::string s = "";
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            s += inf[i];
            s += ' ';
        } else {
            if (inf[i] == '(' || stack0.isEmpty() == 1 ||
                pr[inf[i]] > pr[stack0.get()]) {
                stack0.push(inf[i]);
            } else if (inf[i] == ')') {
                while (stack0.get() != '(') {
                    s = s + stack0.pop() + ' ';
                }
                if (stack0.get() == '(') {
                    stack0.pop();
                }
            } else if (pr[inf[i]] <= pr[stack0.get()]) {
                char item = stack0.pop();
                s = s + item + ' ';
                stack0.push(inf[i]);
            }
        }
    }
    while (stack0.isEmpty() != 1) {
        s = s + stack0.pop();
        if (stack0.isEmpty() != 1) {
            s += ' ';
        }
    }
    return s;
}

int eval(std::string pref) {
    std::string sPer;
    char cPer;
    for (char i : pref) {
        if ((i >= '0' && i <= '9')) {
            sPer += i;
        } else if (!sPer.empty() && i == ' ') {
            stackend.push(std::stoi(sPer));
            sPer.clear();
        } else {
            switch (i) {
                case '+': {
                    cPer = stackend.pop();
                    stackend.push(stackend.pop() + cPer);
                    break;
                }
                case '-': {
                    cPer = stackend.pop();
                    stackend.push(stackend.pop() - cPer);
                    break;
                }
                case '*': {
                    cPer = stackend.pop();
                    stackend.push(stackend.pop() * cPer);
                    break;
                }
                case '/': {
                    cPer = stackend.pop();
                    stackend.push(stackend.pop() / cPer);
                    break;
                }
            }
        }
    }
    return stackend.pop();
}
