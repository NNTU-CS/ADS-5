// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int Prioritet(char ch) {
    switch (ch) {
    case '(':
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
}

std::string infx2pstfx(const std::string& inf) {
    std::string pstfx;
    TStack<char, 50> stack;
    if (inf.length() == 0) {
        throw "Is empty";
    }
    for (int i = 0;i < inf.length();i++) {
        if (isDigit(inf[i])) {
            std::string value;
            value += inf[i];
            while (isDigit(inf[++i]))
            {
                value += inf[i];
            }
            pstfx += value;
            pstfx += ' ';
            i--;    
        } else if (inf[i] == '(') {
            stack.Push(inf[i]);
        } else if (inf[i] == ')') {
            while (!stack.isEmpty() && stack.peekLast() != '(') {
                pstfx += stack.pop();
                pstfx += ' ';
            }
            if (!stack.isEmpty()) {
                stack.pop();
            }
        } else if (isOperator(inf[i])) {
            while (!stack.isEmpty() && (Prioritet(inf[i]) <= Prioritet(stack.peekLast()))) {
                pstfx += stack.pop();
                pstfx += ' ';
            }
            stack.Push(inf[i]);
        }   
    }
    while (!stack.isEmpty())
    {
        pstfx += stack.pop();
        pstfx += ' ';
    }
    pstfx.pop_back();
    return pstfx;
}

int eval(const std::string& pref) {
    TStack<int, 50>stack;
    for (int i = 0;i < pref.length();i++) {
        if (isdigit(pref[i])) {
            std::string value;
            value += pref[i];
            while (isDigit(pref[++i]))
            {
                value += pref[i];
            }
            stack.Push(std::stoi(value));
        }
        else if(isOperator(pref[i])) {
            int r_num = stack.peekLast();
            stack.pop();
            int l_num = stack.peekLast();
            stack.pop();
            switch (pref[i])
            {
            case '+':
                stack.Push(l_num + r_num);
                break;
            case '-':
                stack.Push(l_num - r_num);
                break;
            case '*':
                stack.Push(l_num * r_num);
                break;
            case '/':
                stack.Push(l_num / r_num);
                break;
            case ' ':
                break;
            }
        }
    }
    return stack.pop();
}
