// Copyright 2025 NNTU-CS
#include "include/alg.h"
#include "include/tstack.h"
#include <string>
#include <sstream>
#include <cctype>
#include <map>

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string out;
    size_t i = 0;

    std::map<char, int> priority = {
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2}
    };

    while (i < inf.length()) {
        char c = inf[i];

        if (std::isspace(c)) {
            ++i;
            continue;
        } else if (std::isdigit(c)) {
            while (i < inf.length() && std::isdigit(inf[i])) {
                out += inf[i++];
            }
            out += ' ';
            continue;
        } else if (c == '(') {
            stack.Put(c);
        } else if (c == ')') {
            while (!stack.IsEmpty() && stack.TopElem() != '(') {
                out += stack.TopElem();
                out += ' ';
                stack.Get();
            }
            if (!stack.IsEmpty()) {
                stack.Get(); // убираем '('
            }
        } else { // оператор + - * /
            while (!stack.IsEmpty() && stack.TopElem() != '(' &&
                   priority[stack.TopElem()] >= priority[c]) {
                out += stack.TopElem();
                out += ' ';
                stack.Get();
            }
            stack.Put(c);
        }
        ++i;
    }

    while (!stack.IsEmpty()) {
        out += stack.TopElem();
        out += ' ';
        stack.Get();
    }

    if (!out.empty() && out.back() == ' ') {
        out.pop_back();
    }
    return out;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::stringstream ss(post);
    std::string token;

    while (ss >> token) {
        if (std::isdigit(token[0])) {
            stack.Put(std::stoi(token));
        } else {
            int b = stack.TopElem(); stack.Get();
            int a = stack.TopElem(); stack.Get();
            if (token == "+") {
                stack.Put(a + b);
            } else if (token == "-") {
                stack.Put(a - b);
            } else if (token == "*") {
                stack.Put(a * b);
            } else if (token == "/") {
                stack.Put(a / b);
            }
        }
    }
    return stack.TopElem();
}
