// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string post;
    int n = inf.length();

    for (int i = 0; i < n; ++i) {
        char c = inf[i];

        if (isdigit(c)) {
            while (i < n && isdigit(inf[i])) {
                post += inf[i];
                i++;
            }
            post += ' ';
            i--;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                post += stack.pop();
                post += ' ';
            }
            if (!stack.isEmpty()) stack.pop(); // убрать '('
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.isEmpty() && priority(stack.top()) >= priority(c)) {
                post += stack.pop();
                post += ' ';
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        post += stack.pop();
        post += ' ';
    }

    return post;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    int n = post.length();

    for (int i = 0; i < n; ++i) {
        char c = post[i];

        if (isdigit(c)) {
            int num = 0;
            while (i < n && isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                i++;
            }
            stack.push(num);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            int b = stack.pop();
            int a = stack.pop();
            int res = 0;

            if (c == '+') res = a + b;
            else if (c == '-') res = a - b;
            else if (c == '*') res = a * b;
            else if (c == '/') res = a / b;

            stack.push(res);
        }
    }

    return stack.top();
}
