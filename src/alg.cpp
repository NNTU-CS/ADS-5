// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include "tstack.h"

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

std::string infx2pstfx(const std::string& inf) {
    std::string result;
    TStack<char, 100> stack;
    std::string number;

    for (size_t i = 0; i < inf.size(); ++i) {
        char ch = inf[i];

        if (std::isdigit(ch)) {
            number += ch;
        } else {
            if (!number.empty()) {
                result += number + " ";
                number.clear();
            }

            if (ch == '(') {
                stack.push(ch);
            } else if (ch == ')') {
                char topOp;
                while (!stack.isEmpty() && stack.top(topOp) && topOp != '(') {
                    stack.pop(topOp);
                    result += topOp;
                    result += " ";
                }
                if (!stack.isEmpty()) {
                    stack.pop(topOp); // удалить '('
                }
            } else if (is_operator(ch)) {
                char topOp;
                while (!stack.isEmpty() && stack.top(topOp) &&
                       is_operator(topOp) && priority(topOp) >= priority(ch)) {
                    stack.pop(topOp);
                    result += topOp;
                    result += " ";
                }
                stack.push(ch);
            }
        }
    }

    if (!number.empty()) {
        result += number + " ";
    }

    char remaining;
    while (!stack.isEmpty()) {
        stack.pop(remaining);
        result += remaining;
        result += " ";
    }

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream in(post);
    std::string token;

    while (in >> token) {
        if (std::isdigit(token[0])) {
            stack.push(std::stoi(token));
        } else if (token.length() == 1 && is_operator(token[0])) {
            int b, a;
            if (!stack.pop(b) || !stack.pop(a)) {
                // Ошибка: недостаточно операндов
                return 0;
            }

            int result = 0;
            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) return 0; // деление на ноль
                    result = a / b;
                    break;
            }
            stack.push(result);
        }
    }

    int res = 0;
    if (!stack.pop(res)) {
        return 0;
    }
    return res;
}
