// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    std::string result;
    TStack<char, 100> stack;
    std::map<char, int> precedence = {
        {'*', 3}, {'/', 3}, {'+', 2}, {'-', 2}, {'(', 1}};

    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (isdigit(c)) {
            // Собираем многозначные числа
            while (i < inf.size() && isdigit(inf[i])) {
                result += inf[i++];
            }
            result += ' ';
            i--; // Возвращаемся на один символ назад
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                result += stack.pop();
                result += ' ';
            }
            stack.pop(); // Удаляем '(' из стека
        } else if (precedence.count(c)) {
            while (!stack.isEmpty() && stack.top() != '(' &&
                   precedence[stack.top()] >= precedence[c]) {
                result += stack.pop();
                result += ' ';
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        result += stack.pop();
        result += ' ';
    }

    if (!result.empty()) {
        result.pop_back(); // Удаляем последний пробел
    }

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    int num = 0;
    bool readingNum = false;

    for (char c : post) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
            readingNum = true;
        } else if (c == ' ') {
            if (readingNum) {
                stack.push(num);
                num = 0;
                readingNum = false;
            }
        } else {
            int b = stack.pop();
            int a = stack.pop();
            switch (c) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
            }
        }
    }

    return stack.top();
}
