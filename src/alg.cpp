// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int getOperatorPriority(char operation) {
    switch (operation) {
        case '(': return 0;
        case ')': return 1;
        case '+': case '-': return 2;
        case '*': case '/': return 3;
        default: return -1;
    }
}

std::string infx2pstfx(const std::string& inf) {
    std::string output;
    TStack<char, 100> operatorStack;
    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];
        if (c == ' ') continue;

        if (std::isdigit(c)) {
            while (i < inf.length() && std::isdigit(inf[i])) {
                output += inf[i++];
            }
            output += ' ';
            i--;
        } else if (c == '(') {
            operatorStack.insertElement(c);
        } else if (c == ')') {
            while (!operatorStack.isEmpty() && operatorStack.peekTop() != '(') {
                output += operatorStack.peekTop();
                output += ' ';
                operatorStack.removeLast();
            }
            if (operatorStack.isEmpty()) {
                throw std::runtime_error("Mismatched parentheses");
            }
            operatorStack.removeLast();
        } else {
            while (!operatorStack.isEmpty() &&
                   getOperatorPriority(operatorStack.peekTop()) >=
                   getOperatorPriority(c)) {
                output += operatorStack.peekTop();
                output += ' ';
                operatorStack.removeLast();
            }
            operatorStack.insertElement(c);
        }
    }

    while (!operatorStack.isEmpty()) {
        if (operatorStack.peekTop() == '(') {
            throw std::runtime_error("Mismatched parentheses");
        }
        output += operatorStack.peekTop();
        output += ' ';
        operatorStack.removeLast();
    }

    if (!output.empty() && output.back() == ' ') {
        output.pop_back();
    }
    return output;
}

int eval(const std::string& pref) {
    TStack<int, 100> numberStack;
    std::istringstream iss(pref);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0])) {
            numberStack.insertElement(std::stoi(token));
        } else if (token.size() == 1) {
            if (numberStack.isEmpty()) {
                throw std::runtime_error("Missing operands");
            }
            int b = numberStack.removeLast();
            if (numberStack.isEmpty()) {
                throw std::runtime_error("Missing operands");
            }
            int a = numberStack.removeLast();

            switch (token[0]) {
                case '+': numberStack.insertElement(a + b); break;
                case '-': numberStack.insertElement(a - b); break;
                case '*': numberStack.insertElement(a * b); break;
                case '/':
                    if (b == 0) throw std::runtime_error("Division by zero");
                    numberStack.insertElement(a / b);
                    break;
                default: throw std::runtime_error("Invalid operator");
            }
        } else {
            throw std::runtime_error("Invalid token");
        }
    }

    if (numberStack.isEmpty()) throw std::runtime_error("No result");
    int result = numberStack.removeLast();
    if (!numberStack.isEmpty()) throw std::runtime_error("Extra operands");
    return result;
}
