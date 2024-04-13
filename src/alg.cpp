// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::map<char, int> priority {
        {'(', 0}, {')', 1}, {'-', 2}, {'+', 2}, {'/', 3}, {'*', 3}
};
TStack<char, 100> stack1;
TStack<int, 100> stack2;

std::string infx2pstfx(std::string inf) {
    std::string s = "";
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            s += inf[i];
            s += ' ';
        } else {
            if (inf[i] == '(' || stack1.isEmpty() == 1 ||
            priority[inf[i]] > priority[stack1.get()]) {
                stack1.push(inf[i]);
            } else if (inf[i] == ')') {
                while (stack1.get() != '(') {
                    s = s + stack1.pop() + ' ';
                }
                if (stack1.get() == '(') {
                    stack1.pop();
                }
            } else if (priority[inf[i]] <= priority[stack1.get()]) {
                char item = stack1.pop();
                s = s + item + ' ';
                stack1.push(inf[i]);
            }
        }
    }
    while (stack1.isEmpty() != 1) {
        s = s + stack1.pop();
        if (stack1.isEmpty() != 1) {
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
            stack2.push(std::stoi(sPer));
            sPer.clear();
        } else {
            switch (i) {
                case '+': {
                    cPer = stack2.pop();
                    stack2.push(stack2.pop() + cPer);
                    break;
                }
                case '*': {
                    cPer = stack2.pop();
                    stack2.push(stack2.pop() * cPer);
                    break;
                }
                case '/': {
                    cPer = stack2.pop();
                    stack2.push(stack2.pop() / cPer);
                    break;
                }
                case '-': {
                    cPer = stack2.pop();
                    stack2.push(stack2.pop() - cPer);
                    break;
                }
            }
        }
    }
    return stack2.pop();
}
