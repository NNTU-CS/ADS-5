// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string output;
    size_t i = 0;
    while (i < inf.size()) {
        if (std::isspace(inf[i])) {
            ++i;
            continue;
        }
        if (std::isdigit(inf[i])) {
            while (i < inf.size() && std::isdigit(inf[i])) {
                output += inf[i++];
            }
            output += ' ';
        } else if (inf[i] == '(') {
            stack.push('(');
            ++i;
        } else if (inf[i] == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                output += stack.top();
                output += ' ';
                stack.pop();
            }
            if (!stack.isEmpty() && stack.top() == '(') stack.pop();
            ++i;
        } else {
            while (!stack.isEmpty() && precedence(stack.top()) >= precedence(inf[i])) {
                output += stack.top();
                output += ' ';
                stack.pop();
            }
            stack.push(inf[i]);
            ++i;
        }
    }
    while (!stack.isEmpty()) {
        output += stack.top();
        output += ' ';
        stack.pop();
    }
    if (!output.empty() && output.back() == ' ') output.pop_back();
    return output;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    size_t i = 0;
    while (i < post.size()) {
        if (std::isspace(post[i])) {
            ++i;
            continue;
        }
        if (std::isdigit(post[i])) {
            int val = 0;
            while (i < post.size() && std::isdigit(post[i])) {
                val = val * 10 + (post[i] - '0');
                ++i;
            }
            stack.push(val);
        } else {
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            int res = 0;
            switch (post[i]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
            }
            stack.push(res);
            ++i;
        }
    }
    return stack.top();
}
