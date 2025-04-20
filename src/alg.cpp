// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  std::string res;
    TStack<char, 100> stack;
    std::map<char, int> precedence = {
        {'*', 3}, {'/', 3}, {'+', 2}, {'-', 2}, {'(', 1}
    };

    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (isdigit(c)) {
            while (i < inf.size() && isdigit(inf[i])) {
                res += inf[i++];
            }
            res += ' ';
            --i;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.top(c)) {
                res += c;
                res += ' ';
            }
            stack.pop(c);
        } else if (precedence.count(c)) {
            while (!stack.isEmpty() && stack.top(c) && stack.top(c) != '(' &&
                   precedence[stack.top(c)] >= precedence[c]) {
                res += c;
                res += ' ';
                stack.pop(c);
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        res += stack.pop();
        res += ' ';
    }

    if (!res.empty()) {
        res.pop_back();
    }

    return res;
}

int eval(const std::string& pref) {
      TStack<int, 100> stack;
    int num = 0;
    bool parsingNumber = false;

    for (char c : pref) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
            parsingNumber = true;
        } else if (c == ' ') {
            if (parsingNumber) {
                stack.push(num);
                num = 0;
                parsingNumber = false;
            }
        } else {
            int b = 0;
            int a = 0;
            stack.pop(b);
            stack.pop(a);
            switch (c) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
            }
        }
    }

    int res = 0;
    stack.top(res);
    return res;
}
