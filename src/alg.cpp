// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include <cctype>
#include <sstream>
#include <stdexcept>

namespace {

int prec(char gg) {
    switch (gg) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    }
}

int apply(int a, int b, char gg) {
    switch (gg) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("division by zero");
            return a / b;
        default:  throw std::runtime_error("unknown operator");
    }
}

}

std::string infx2pstfx(const std::string& inf) {
   TStack<char, 100> gg;
    std::string res;

    for (size_t i = 0; i < inf.size(); ) {

        if (std::isspace(inf[i])) { ++i; continue; }

        if (std::isdigit(inf[i])) {
            while (i < inf.size() && std::isdigit(inf[i]))
                res.push_back(inf[i++]);
            res.push_back(' ');
            continue;
        }

        char c = inf[i];
        if (c == '(') {
            gg.push(c);
            ++i;
        } else if (c == ')') {
            while (!gg.empty() && gg.top() != '(') {
                res.push_back(gg.top()); res.push_back(' ');
                gg.pop();
            }
            if (gg.empty()) throw std::runtime_error("mismatched parenthesis");
            gg.pop();
            ++i;
        } else {
            while (!gg.empty() && prec(gg.top()) >= prec(c)) {
                res.push_back(gg.top()); res.push_back(' ');
                gg.pop();
            }
            gg.push(c);
            ++i;
        }
    }

    while (!gg.empty()) {
        if (gg.top() == '(') throw std::runtime_error("mismatched parenthesis");
        res.push_back(gg.top()); res.push_back(' ');
        gg.pop();
    }

    if (!res.empty() && res.back() == ' ') res.pop_back();
    return res;
}

int eval(const std::string& post)
{
    TStack<int, 100> st;
    std::istringstream ss(post);

    std::string tok;
    while (ss >> tok) {
        if (std::isdigit(tok[0])) {
            st.push(std::stoi(tok));
        } else {
            if (st.size() < 2)
                throw std::runtime_error("not enough operands");

            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            st.push(apply(a, b, tok[0]));
        }
    }

    if (st.size() != 1)
        throw std::runtime_error("wrong postfix expression");

    return st.top();
}
