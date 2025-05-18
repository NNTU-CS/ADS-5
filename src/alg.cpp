// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

static int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& infix) {
    TStack<char, 100> opStack;
    std::ostringstream postfix;
    size_t i = 0;

    while (i < infix.size()) {
        char ch = infix[i];

        if (std::isdigit(ch)) {
            while (i < infix.size() && std::isdigit(infix[i])) {
                postfix << infix[i++];
            }
            postfix << ' ';
            --i;
        } else if (ch == '(') {
            opStack.push(ch);
        } else if (ch == ')') {
            while (!opStack.empty() && opStack.peek() != '(') {
                postfix << opStack.pop() << ' ';
            }
            if (!opStack.empty()) opStack.pop(); // Remove '('
        } else if (ch == '+'  ch == '-'  ch == '*' || ch == '/') {
            while (!opStack.empty() && getPrecedence(opStack.peek()) >= getPrecedence(ch)) {
                postfix << opStack.pop() << ' ';
            }
            opStack.push(ch);
        }
        ++i;
    }

    while (!opStack.empty()) {
        postfix << opStack.pop() << ' ';
    }

    std::string res = postfix.str();
    if (!res.empty() && res.back() == ' ') res.pop_back();
    return res;
}

int eval(const std::string& postfix) {
    TStack<int, 100> valStack;
    std::istringstream iss(postfix);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0])) {
            valStack.push(std::stoi(token));
        } else {
            int right = valStack.pop();
            int left = valStack.pop();
            switch (token[0]) {
                case '+': valStack.push(left + right); break;
                case '-': valStack.push(left - right); break;
                case '*': valStack.push(left * right); break;
                case '/': valStack.push(left / right); break;
            }
        }
    }

    return valStack.pop();
}
