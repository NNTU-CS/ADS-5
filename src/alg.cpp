// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include <sstream>
#include "tstack.h"

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    std::string post;
    TStack<char, 100> ops;
    for (size_t i = 0; i < inf.size(); ++i) {
        if (isdigit(inf[i])) {
            while (i < inf.size() && isdigit(inf[i])) {
                post += inf[i++];
            }
            post += ' ';
            --i;
        } else if (inf[i] == '(') {
            ops.push(inf[i]);
        } else if (inf[i] == ')') {
            while (!ops.isEmpty() && ops.peek() != '(') {
                post += ops.pop();
                post += ' ';
            }
            if (!ops.isEmpty()) ops.pop();
        } else if (inf[i] == '+' || 
            inf[i] == '-' || inf[i] == '*' || inf[i] == '/') {
            while (!ops.isEmpty() && priority(inf[i]) <= priority(ops.peek())) {
                post += ops.pop();
                post += ' ';
            }
            ops.push(inf[i]);
        }
    }
    while (!ops.isEmpty()) {
        post += ops.pop();
        post += ' ';
    }
    return post;
}

int eval(const std::string& post) {
    TStack<int, 100> st;
    std::istringstream ss(post);
    std::string token;
    while (ss >> token) {
        if (isdigit(token[0])) {
            st.push(std::stoi(token));
        } else {
            int b = st.pop();
            int a = st.pop();
            switch (token[0]) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
            }
        }
    }
    return st.pop();
}
