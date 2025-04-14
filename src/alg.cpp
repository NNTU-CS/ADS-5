// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "tstack.h"

int prioritet(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

bool opperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack1;
    std::ostringstream result;
    bool flag = false;
    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (std::isspace(c)) continue;
        if (std::isdigit(c)) {
            if (flag)
            {
                result << ' ';
            }
            while (i < inf.size() && std::isdigit(inf[i]))
            {
                result << inf[i++];
            }
            i--;
            flag = true;
        }
        else if (c == '(')
        {
            stack1.push(c);
            flag = false;
        } else if (c == ')')
        {
            while (!stack1.isEmpty() && stack1.peek() != '(')
            {
                result << ' ' << stack1.pop();
            }
            if (!stack1.isEmpty() && stack1.peek() == '(')
            {
                stack1.pop();
            }
            flag = true;
        } else if (opperator(c))
        {
            while (!stack1.isEmpty() && stack1.peek() != '(' && prioritet(c) <= prioritet(stack1.peek()))
            {
                result << ' ' << stack1.pop();
            }
            stack1.push(c);
            flag = true;
        } else {
            throw std::invalid_argument("Invalid character");
        }
    }
    while (!stack1.isEmpty())
    {
        result << ' ' << stack1.pop();
    }
    return result.str();
}

int eval(const std::string& post) {
    TStack<int, 100> stack2;
    std::istringstream iss(post);
    std::string token;
    while (iss >> token)
    {
        if (std::isdigit(token[0]))
        {
            stack2.push(std::stoi(token));
        } else if (opperator(token[0]) && token.size() == 1)
        {
            if (stack2.isEmpty()) throw std::invalid_argument("Not enough operands");
            int right = stack2.pop();
            if (stack2.isEmpty()) throw std::invalid_argument("Not enough operands");
            int left = stack2.pop();
            switch (token[0])
            {
                case '+': stack2.push(left + right); break;
                case '-': stack2.push(left - right); break;
                case '*': stack2.push(left * right); break;
                case '/':
                    if (right == 0) throw std::runtime_error("Division by zero");
                    stack2.push(left / right);
                    break;
            }
        } else {
            throw std::invalid_argument("Invalid token");
        }
    }
    if (stack2.isEmpty()) throw std::invalid_argument("Empty expression");
    int result = stack2.pop();
    if (!stack2.isEmpty()) throw std::invalid_argument("Too many operands");
    return result;
}
