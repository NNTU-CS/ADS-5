// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

static std::map<char, int> precedence = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result;
    
    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];
        
        if (isdigit(c)) {
            while (i < inf.length() && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            --i;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                result += stack.top();
                result += ' ';
                stack.pop();
            }
            if (!stack.isEmpty()) {
                stack.pop();
            }
        } else if (isOperator(c)) {
            while (!stack.isEmpty() && stack.top() != '(' &&
                   precedence[c] <= precedence[stack.top()]) {
                result += stack.top();
                result += ' ';
                stack.pop();
            }
            stack.push(c);
        }
    }
    
    while (!stack.isEmpty()) {
        result += stack.top();
        result += ' ';
        stack.pop();
    }
    
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::string num;
    
    for (size_t i = 0; i < post.length(); ++i) {
        char c = post[i];
        
        if (c == ' ') {
            continue;
        }
        
        if (isdigit(c)) {
            num.clear();
            while (i < post.length() && (isdigit(post[i]) || post[i] == ' ')) {
                if (post[i] != ' ') {
                    num += post[i];
                } else {
                    break;
                }
                ++i;
            }
            stack.push(std::stoi(num));
            --i;
        } else if (isOperator(c)) {
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            
            switch (c) {
                case '+':
                    stack.push(a + b);
                    break;
                case '-':
                    stack.push(a - b);
                    break;
                case '*':
                    stack.push(a * b);
                    break;
                case '/':
                    stack.push(a / b);
                    break;
            }
        }
    }
    
    return stack.top();
}
