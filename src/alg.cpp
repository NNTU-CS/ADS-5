// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string post;
    for (size_t i = 0; i < inf.length(); ++i) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            while (i < inf.length() && inf[i] >= '0' && inf[i] <= '9') {
                post += inf[i];
                i++;
            }
            post += ' ';
            i--;
        } else if (inf[i] == '(') {
            stack.push('(');
        } else if (inf[i] == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                post += stack.pop();
                post += ' ';
            }
            if (!stack.isEmpty())
                stack.pop();
        } else if (inf[i] == '+' ||
            inf[i] == '-' ||
            inf[i] == '*' ||
            inf[i] == '/') {
            while (!stack.isEmpty() &&
                getPriority(stack.peek()) >= getPriority(inf[i])) {
                post += stack.pop();
                post += ' ';
            }
            stack.push(inf[i]);
        }
    }
    while (!stack.isEmpty()) {
        post += stack.pop();
        post += ' ';
    }
    if (!post.empty() && post.back() == ' ')
        post.pop_back();
    return post;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    size_t i = 0;
    while (i < post.length()) {
        if (post[i] >= '0' && post[i] <= '9') {
            int num = 0;
            while (i < post.length() && post[i] >= '0' && post[i] <= '9') {
                num = num * 10 + (post[i] - '0');
                i++;
            }
            stack.push(num);
        } else if (post[i] == '+' ||
            post[i] == '-' ||
            post[i] == '*' ||
            post[i] == '/') {
            int b = stack.pop();
            int a = stack.pop();
            int res = 0;
            if (post[i] == '+') res = a + b;
            else if (post[i] == '-') res = a - b;
            else if (post[i] == '*') res = a * b;
            else if (post[i] == '/') res = a / b;
            stack.push(res);
            i++;
        } else {
            i++;
        }
    }
    return stack.pop();
}
