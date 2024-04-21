// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::map<char, int>  priority  = {{'(', 0}, { ')', 1}, { '+', 2},
                                      { '-', 2}, { '*', 3}, { '/', 3} };
    std::string res_str = "";
    for (int i = 0; i < inf.length(); i++) {
        if ('0' <= inf[i] && inf[i] <= '9') {
            res_str += inf[i];
            res_str += " ";
        } else if (inf[i] == '(') {
            stack1.Push(inf[i]);
        } else if (inf[i] == ')') {
            while (!stack1.IsEmpty() && stack1.Top() != '(') {
                res_str += stack1.Pop();
                res_str += " ";
            }
            stack1.Pop();
        } else if (inf[i] == '+' || inf[i] == '-'
                   || inf[i] == '*' || inf[i] == '/') {
            while ( !stack1.IsEmpty()
                   && priority[inf[i]] <= priority[stack1.Top()]) {
                res_str += stack1.Pop();
                res_str += " ";
            }
            stack1.Push(inf[i]);
        }
    }
    while (!stack1.IsEmpty()) {
        res_str += stack1.Pop();
        res_str += " ";
    }
    res_str.erase(res_str.length() - 1);
    return res_str;
}

int eval(std::string pref) {
    TStack<int, 100> stack2;
    for (int i = 0; i < pref.length(); i++) {
        if ('0' <= pref[i] && pref[i] <= '9') {
            stack2.Push(pref[i] - '0');
        } else if (pref[i] == '+') {
            stack2.Push(stack2.Pop() + stack2.Pop());
        } else if (pref[i] == '-') {
            int num2 = stack2.Pop();
            int num1 = stack2.Pop();
            stack2.Push(num1 - num2);
        } else if (pref[i] == '*') {
            stack2.Push(stack2.Pop() * stack2.Pop());
        } else if (pref[i] == '/') {
            int num2 = stack2.Pop();
            int num1 = stack2.Pop();
            stack2.Push(num1 / num2);
        }
    }
    return stack2.Top();
}
