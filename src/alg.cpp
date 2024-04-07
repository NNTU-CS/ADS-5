// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

TStack<char, 100> stack1;
TStack<int, 100> stack2;
std::map<char, int> p {
    {'(', 0}, {')', 1}, {'+', 2}, {'-', 2}, {'*', 3}, {'/', 3}
};

std::string infx2pstfx(std::string inf) {
    std::string str = "";
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
          str += inf[i];
          str += ' ';
        } else {
            if (stack1.isEmpty() == 1 || inf[i] == '(' ||
                p[inf[i]] > p[stack1.get()]) {
              stack1.push(inf[i]);
            } else if (inf[i] == ')') {
                while (stack1.get() != '(') {
                  str = str + stack1.pop() + ' ';
                }
                if (stack1.get() == '(') {
                  stack1.pop();
                }
            } else if (p[inf[i]] <= p[stack1.get()]) {
              char item = stack1.pop();
              str = str + item + ' ';
              stack1.push(inf[i]);
            }
        }
    }
    while (stack1.isEmpty() != 1) {
        str = str + stack1.pop();
        if (stack1.isEmpty() != 1) {
            str += ' ';
        }
    }
    return str;
}

int eval(std::string pref) {
    std::string str1;
    char item;
    for (char i : pref) {
        if ((i >= '0' && i <= '9')) {
            str1 += i;
        } else if (!str1.empty() && i == ' ') {
            stack2.push(std::stoi(str1));
            str1.clear();
        } else {
            switch (i) {
                case '*': {
                    item = stack2.pop();
                    stack2.push(stack2.pop() * item);
                    break;
                }
                case '/': {
                    item = stack2.pop();
                    stack2.push(stack2.pop() / item);
                    break;
                }
                case '+': {
                    item = stack2.pop();
                    stack2.push(stack2.pop() + item);
                    break;
                }
                case '-': {
                    item = stack2.pop();
                    stack2.push(stack2.pop() - item);
                    break;
                }
            }
        }
    }
    return stack2.pop();
}

