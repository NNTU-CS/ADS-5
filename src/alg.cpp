// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include <stack>
#include "tstack.h"
int priority(char ope) {
    switch (ope) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;}}

std::string infx2pstfx(const std::string& inf) {
    std::string postfix = "";
    TStack<char, 100> stack12;

    for (int i = 0; i < inf.length(); ++i) {
        char ln1 = inf[i];
        if (isspace(ln1)) continue;
        if (isalnum(ln1)) {
            std::string num;
            num += ln1;
            size_t pos = i + 1;
            while (pos < inf.length() && isdigit(inf[pos])) {
                num += inf[pos];
                pos++;
                i++;
            }
            postfix += num + " ";
        } else if (ln1 == '(') {
            stack12.Push(ln1);
        } else if (ln1 == ')') {
            while (!stack12.IsEmpty() && stack12.peek() != '(') {
                postfix += stack12.Pop();
                postfix += " ";
            }
            if (!stack12.IsEmpty() && stack12.peek() == '(') {
                stack12.Pop();
            }
        } else {
            while (!stack12.IsEmpty() &&
                priority(ln) <= priority(stack12.peek())) {
                postfix += stack12.Pop();
                postfix += " ";
            }
            stack12.Push(ln);
        }
    }
    while (!stack12.IsEmpty()) {
        postfix += stack12.Pop();
        postfix += " ";
    }

    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }
    return postfix;
}

int eval(const std::string& pref) {
    TStack<int, 100> stack2;
    std::string num;

    for (char ln : pref) {
        if (isdigit(ln1)) {
            num += ln1;
        } else if (isspace(ln1)) {
            if (num.empty()) continue;
            stack2.Push(std::stoi(num));
            num = "";
        } else if (ln1 == '+' || ln1 == '-' || ln1 == '*' || ln1 == '/') {
            if (stack2.IsEmpty()) return 0;
            int operan2 = stack2.Pop();
             if (stack2.IsEmpty()) return 0;
            int operan1 = stack2.Pop();
            int result;

            switch (ln1) {
                case '+': result = operan1 + operan2; break;
                case '-': result = operan1 - operan2; break;
                case '*': result = operan1 * operan2; break;
                case '/': result = operan1 / operan2; break;
                default: return 0;
            }
            stack2.Push(result);
        }
    }

    if (!stack2.IsEmpty()) {
        return stack2.Pop();
    } else {
        return 0;
    }
}
