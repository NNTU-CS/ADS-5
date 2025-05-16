// Copyright 2025 NNTU-CS
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>
#include "tstack.h"
using namespace std;

static int precedence(char op) {
    return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2 : 0;
}

static inline bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

string infx2pstfx(const string& inf) {
    TStack<char, 128> ops;
    string out;
    for (size_t i = 0; i < inf.size(); ++i) {
        char ch = inf[i];
        if (isspace(static_cast<unsigned char>(ch))) continue;

        if (isdigit(static_cast<unsigned char>(ch))) {
            while (i < inf.size() && isdigit(static_cast<unsigned char>(inf[i]))) {
                out += inf[i++];
            }
            out += ' ';
            --i;
        } else if (ch == '(') {
            ops.push(ch);
        } else if (ch == ')') {
            while (!ops.isEmpty() && ops.top() != '(') {
                out += ops.pop();
                out += ' ';
            }
            if (!ops.isEmpty()) ops.pop();
        } else if (isOp(ch)) {
            while (!ops.isEmpty() && isOp(ops.top()) && 
                   precedence(ops.top()) >= precedence(ch)) {
                out += ops.pop();
                out += ' ';
            }
            ops.push(ch);
        }
    }
    
    while (!ops.isEmpty()) {
        out += ops.pop();
        out += ' ';
    }
    
    if (!out.empty() && out.back() == ' ') out.pop_back();
    return out;
}

int eval(const string& post) {
    TStack<int, 128> st;
    istringstream ss(post);
    string token;
    
    while (ss >> token) {
        if (token.size() == 1 && isOp(token[0])) {
            switch (token[0]) {
                case '+': st.push(lhs + rhs); break;
                case '-': st.push(lhs - rhs); break;
                case '*': st.push(lhs * rhs); break;
                case '/': st.push(lhs / rhs); break;
            }
        } else {
            st.push(stoi(token));
        }
    }
    
    int result = st.pop();
    if (!st.isEmpty()) throw runtime_error("Too many operands");
    return result;
}
