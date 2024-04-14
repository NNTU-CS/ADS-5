// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <map>
#include "tstack.h"

TStack<char, 100> stack1;
TStack<int, 100> stack2;

int Prioritet(char a) {
    switch (a) {
    case '(': {
        return 0;
    }
    case ')': {
        return 1;
    }
    case '+':
    case '-': {
        return 2;
    }
    case '*':
    case '/': {
        return 3;
    }
    }
    return -1;
}

std::string infx2pstfx(std::string inf) {
    std::string result = "";
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            result += inf[i];
            result += ' ';
        } else {
            if (stack1.isEmpty() == 1 || inf[i] == '('
                || Prioritet(inf[i]) > Prioritet(stack1.get())) {
                stack1.push(inf[i]);
            } else if (inf[i] == ')') {
                while (stack1.get() != '(') {
                    result = result + stack1.pop() + ' ';
                }
                if (stack1.get() == '(') {
                    stack1.pop();
                }
            } else if (Prioritet(inf[i]) <= Prioritet(stack1.get())) {
                char ch = stack1.pop();
                result = result + ch + ' ';
                stack1.push(inf[i]);
            }
        }
    }
    while (stack1.isEmpty() != 1) {
        result += stack1.pop();
        if (stack1.isEmpty() != 1) {
            result += ' ';
        }
    }
    return result;
}

int eval(std::string pref) {
    std::string result;
    char cha;
    for (char i : pref) {
        if (i >= '0' && i <= '9') {
            result += i;
        } else if (!result.empty() && i == ' ') {
            stack2.push(std::stoi(result));
            result.clear();
        } else {
            switch (i) {
            case '+': {
                cha = stack2.pop();
                stack2.push(stack2.pop() + cha);
                break;
            }
            case '-': {
                cha = stack2.pop();
                stack2.push(stack2.pop() - cha);
                break;
            }
            case '*': {
                cha = stack2.pop();
                stack2.push(stack2.pop() * cha);
                break;
            }
            case '/': {
                cha = stack2.pop();
                stack2.push(stack2.pop() / cha);
                break;
            }
            }
        }
    }
    return stack2.pop();
}
