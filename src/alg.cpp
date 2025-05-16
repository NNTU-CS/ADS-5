// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include <sstream>
#include <stdexcept>


int priority(char op) {
    switch(op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '(': return 0;
        default:  return -1;
    }
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
    string output;
    string current_number;

    for (char c : inf) {
        if (isdigit(c)) {
            current_number += c;
        } else {
            if (!current_number.empty()) {
                output += current_number + " ";
                current_number.clear();
            }

            if (c == '(') {
                stack.add(c);
            } else if (c == ')') {
                // Выталкиваем операторы до открывающей скобки
                while (!stack.isVoid() && stack.getTop() != '(') {
                    output += stack.remove();
                    output += ' ';
                }
                stack.remove(); // Удаляем '(' из стека
            } else {
                // Выталкиваем операторы с высшим или равным приоритетом
                while (!stack.isVoid() && priority(stack.getTop()) >= priority(c)) {
                    output += stack.remove();
                    output += ' ';
                }
                stack.add(c);
            }
        }
    }

    // Добавляем оставшееся число
    if (!current_number.empty()) {
        output += current_number + " ";
    }

    // Выталкиваем оставшиеся операторы из стека
    while (!stack.isVoid()) {
        output += stack.remove();
        output += ' ';
    }

    // Удаляем лишний пробел в конце
    if (!output.empty() && output.back() == ' ') {
        output.pop_back();
    }

    return output;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack;
    istringstream iss(post);
    string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = stack.remove();
            int a = stack.remove();

            if (token == "+") stack.add(a + b);
            else if (token == "-") stack.add(a - b);
            else if (token == "*") stack.add(a * b);
            else if (token == "/") stack.add(a / b);
        } else {
            stack.add(stoi(token));
        }
    }

    return stack.remove();
}
