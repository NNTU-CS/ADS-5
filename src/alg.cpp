// Copyright 2025 NNTU-CS
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include "tstack.h"

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string op;
    std::istringstream iz(inf);
    std::string tek;

    while (iz >> tek) {
        if (std::isdigit(tek[0])) {
            op += tek + ' ';
        }
        else if (tek[0] == '(') {
            stack.dob('(');
        }
        else if (tek[0] == ')') {
            while (!stack.nepol() && stack.pe() != '(') {
                op += stack.dl();
                op += ' ';
            }
            stack.dl();
        }
        else { 
            while (!stack.nepol() && precedence(stack.pe()) >= precedence(tek[0])) {
                op += stack.dl();
                op += ' ';
            }
            stack.dob(tek[0]);
        }
    }

    while (!stack.nepol()) {
        op += stack.dl();
        op += ' ';
    }

    return op;
}

int eval(const std::string& pref) {
 TStack<int, 100> stack;
 std::istringstream iz(pref);
 std::string tek;

 while (iz >> tek) {
     if (std::isdigit(tek[0])) {
         stack.dob(std::stoi(tek));
     }
     else {
         if (stack.nepol()) {
             int right = stack.dl();
             if (stack.nepol()) {
                 int left = stack.dl();
                 switch (tek[0]) {
                 case '-':
                     stack.dob(left - right);
                     break;
                 case '+':
                     stack.dob(left + right);
                     break;
                 case '/':
                     if (right == 0) {
                         throw std::runtime_error("Division by zero");
                     }
                     stack.dob(left / right);
                     break;
                 case '*':
                     stack.dob(left * right);
                     break;
                 default:
                     throw std::invalid_argument("Unknown operator");
                 }
             }
             else {
                 throw std::runtime_error("Not enough operands");
             }
         }
         else {
             throw std::runtime_error("Not enough operands");
         }
     }
 }

 if (stack.nepol()) {
     return stack.dl();
 }
 else {
     throw std::runtime_error("No result in stack");
 }
}
