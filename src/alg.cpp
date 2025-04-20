// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

static int precedence(char op) {
    return (op == '+' || op == '-') ? 1
        : (op == '*' || op == '/') ? 2
        : 0;
}

static bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> st;
    std::string output;
    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (std::isdigit(c)) {
            std::string num;
            while (i < inf.size() && std::isdigit(inf[i])) {
                num.push_back(inf[i]);
                ++i;
            }
            --i;
            output += num;
            output.push_back(' ');
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                output.push_back(st.top());
                output.push_back(' ');
                st.pop();
            }
            if (!st.empty() && st.top() == '(') {
                st.pop();
            }
        }
        else if (isOperator(c)) {
            while (!st.empty() && isOperator(st.top()) &&
                precedence(st.top()) >= precedence(c)) {
                output.push_back(st.top());
                output.push_back(' ');
                st.pop();
            }
            st.push(c);
        }
        else {
        }
    }
    while (!st.empty()) {
        if (st.top() != '(') {
            output.push_back(st.top());
            output.push_back(' ');
        }
        st.pop();
    }
    if (!output.empty() && output.back() == ' ') {
        output.pop_back();
    }
    return output;
}

int eval(const std::string& post) {
    TStack<int, 100> st;
    std::istringstream iss(post);
    std::string token;
    while (iss >> token) {
        char c = token[0];
        if (token.size() == 1 && isOperator(c)) {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            int res = 0;
            if (c == '+') {
                res = a + b;
            }
            else if (c == '-') {
                res = a - b;
            }
            else if (c == '*') {
                res = a * b;
            }
            else if (c == '/') {
                res = a / b;
            }
            st.push(res);
        }
        else {
            st.push(std::stoi(token));
        }
    }
    return st.top();
}
