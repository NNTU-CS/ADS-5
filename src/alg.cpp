// Copyright 2025 NNTU-CS
#include "tstack.h"
#include <string>
#include <stack>
#include <sstream>
#include <cctype>
#include <stdexcept>
int precedence(char op) {
    switch (op) {
        case '+': 
        case '-': return 1;
        case '*': 
        case '/': return 2;
        default:  return 0;
    }
}
std::string infx2pstfx(const std::string& inf) {
    std::string output;
    TStack<char, 100> stack;
    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (isspace(c)) 
            continue;
        if (isdigit(c)) {
            std::string number;
            while (i < inf.size() && isdigit(inf[i])) {
                number.push_back(inf[i]);
                i++;
            }
            i--;
            if (!output.empty()) 
                output.push_back(' ');
            output += number;
        } 
        else if (c == '(') {
            stack.push(c);
        } 
        else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                output.push_back(' ');
                output.push_back(stack.top());
                stack.pop();
            }
            if (!stack.isEmpty() && stack.top() == '(') {
                stack.pop();
            }
        } 
        else {
            while (!stack.isEmpty() && stack.top() != '(' &&
                   precedence(stack.top()) >= precedence(c)) {
                output.push_back(' ');
                output.push_back(stack.top());
                stack.pop();
            }
            stack.push(c);
        }
    }
    while (!stack.isEmpty()) {
        output.push_back(' ');
        output.push_back(stack.top());
        stack.pop();
    }
    
    return output;
}
int eval(const std::string& pref) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;
    while (iss >> token) {
        if (isdigit(token[0])) {
            int number = std::stoi(token);
            stack.push(number);
        }
        else {
            if (stack.isEmpty())
                throw std::runtime_error("Ошибка.");
            int b = stack.top();
            stack.pop();
            
            if (stack.isEmpty())
                throw std::runtime_error("Ошибка.");
            int a = stack.top();
            stack.pop();
            int result = 0;
            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b == 0)
                        throw std::runtime_error("Ошибка.");
                    result = a / b; 
                    break;
                default:
                    throw std::runtime_error("Ошибка.");
            }
            stack.push(result);
        }
    }
    if (stack.isEmpty())
        throw std::runtime_error("Ошибка.");
    return stack.top();
}
