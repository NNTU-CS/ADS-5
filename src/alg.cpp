// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}
std::string infx2pstfx(const std::string& inf) {
    std::ostringstream out;
    TStack<char, 100> stack;
    int i = 0;
    while (i < inf.length()) {
        if (isspace(inf[i])) {
            i++;
            continue;
        }
        if (isdigit(inf[i])) {
            while (i < inf.length() && isdigit(inf[i])) {
                out << inf[i++];
            }
            out << ' ';
        } else if (inf[i] == '(') {
            stack.push(inf[i]);
            i++;
        } else if (inf[i] == ')') {
            while (!stack.isEmpty() && stack.get() != '(') {
                out << stack.get() << ' ';
                stack.pop();
            }
            if (!stack.isEmpty()) stack.pop();
            i++;
        } else { // оператор
            while (!stack.isEmpty() && priority(stack.get()) >= priority(inf[i])) {
                out << stack.get() << ' ';
                stack.pop();
            }
            stack.push(inf[i]);
            i++;
        }
    }
    while (!stack.isEmpty()) {
        out << stack.get() << ' ';
        stack.pop();
    }
    return out.str();
}
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: throw std::invalid_argument("Invalid operator");
    }
}
int eval(const std::string& pref) {
    std::istringstream in(post);
    std::string token;
    TStack<int, 100> stack;
    while (in >> token) {
        if (isdigit(token[0])) {
            stack.push(std::stoi(token));
        } else if (token.length() == 1 && std::string("+-*/").find(token) != std::string::npos) {
            int b = stack.get(); stack.pop();
            int a = stack.get(); stack.pop();
            stack.push(applyOp(a, b, token[0]));
        }
    }
    return stack.get();
}
