// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <stack>
#include <cctype>
#include <algorithm>
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
    std::stack<char> st;
    std::string output;
    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (std::isdigit(c)) {
            std::string num;
            while (i < inf.size() && std::isdigit(inf[i])) {
                num.push_back(inf[i++]);
            }
            --i;
            output += num;
            output.push_back(' ');
        }else if (c == '(') {
            st.push(c);
        }else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                output.push_back(st.top());
                output.push_back(' ');
                st.pop();
            }
            if (!st.empty()) st.pop();  
        }else if (isOperator(c)) {
            while (!st.empty() && isOperator(st.top()) &&
                precedence(st.top()) >= precedence(c)) {
                output.push_back(st.top());
                output.push_back(' ');
                st.pop();
            }
            st.push(c);
        } 
    }
    while (!st.empty()) {
        if (st.top() != '(') {
            output.push_back(st.top());
            output.push_back(' ');
        }
        st.pop();
    }
    if (!output.empty() && output.back() == ' ')
        output.pop_back();
    return output;
}
int eval(const std::string& post) {
    std::stack<int> st;
    std::istringstream iss(post);
    std::string token;
    while (iss >> token) {
        if (token.size() == 1 && isOperator(token[0])) {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            char op = token[0];
            int res = 0;
            if (op == '+') res = a + b;
            else if (op == '-') res = a - b;
            else if (op == '*') res = a * b;
            else if (op == '/') res = a / b;
            st.push(res);
        }
        else {
            st.push(std::stoi(token));
        }
    }
    return st.top();
}
