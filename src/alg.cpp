// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"


int precedence(char op) {
    static const std::map<char, int> precedenceMap = {
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2}
    };

    auto it = precedenceMap.find(op);
    return (it != precedenceMap.end()) ? it->second : 0;
}

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result;

    for (size_t i = 0; i < inf.length(); ++i) {
        char ch = inf[i];

        if (isDigit(ch)) {
            while (i < inf.length() && isDigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' '; 
            --i; 
        }
 
        else if (ch == '(') {
            if (!stack.push(ch)) {
                return ""; 
            }
        }
        
        else if (ch == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                result += stack.pop();
                result += ' ';
            }
            if (stack.isEmpty()) {
                return ""; 
            }
            stack.pop(); 
        }

        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!stack.isEmpty() && precedence(stack.top()) >= precedence(ch)) {
                result += stack.pop();
                result += ' ';
            }
            if (!stack.push(ch)) {
                return "";
            }
        }
    }

    while (!stack.isEmpty()) {
        result += stack.pop();
        result += ' ';
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

void splitString(const std::string& str, std::string tokens[], int& tokenCount) {
    size_t start = 0;
    size_t end = str.find(' ');
    tokenCount = 0;

    while (end != std::string::npos) {
        tokens[tokenCount++] = str.substr(start, end - start);
        start = end + 1;
        end = str.find(' ', start);
    }

    if (start < str.length()) {
        tokens[tokenCount++] = str.substr(start);
    }
}

int eval(const std::string& post) {
    TStack<int, 100> stack;

    std::string tokens[100];
    int tokenCount = 0;
    splitString(post, tokens, tokenCount);

    for (int i = 0; i < tokenCount; ++i) {
        const std::string& token = tokens[i];

        if (isDigit(token[0])) {
            int value = 0;
            for (char ch : token) {
                value = value * 10 + (ch - '0');
            }
            if (!stack.push(value)) {
                return -1; 
            }
        }
        else {

            int b = stack.pop();
            int a = stack.pop();

            if (token[0] == '+') {
                stack.push(a + b);
            }
            else if (token[0] == '-') {
                stack.push(a - b);
            }
            else if (token[0] == '*') {
                stack.push(a * b);
            }
            else if (token[0] == '/') {
                if (b == 0) {
                    return -1; 
                }
                stack.push(a / b);
            }
            else {
                return -1; 
            }
        }
    }

    return stack.pop();
}
