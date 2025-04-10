// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack1;
    std::string output;
    std::string token;

    for (size_t i = 0; i < inf.length(); ++i) {
        if (isspace(inf[i])) continue;

        if (isdigit(inf[i])) {
            while (i < inf.length() && isdigit(inf[i])) {
                output += inf[i++];
            }
            output += ' ';
            --i;
        } else if (inf[i] == '(') {
            stack1.push('(');
        } else if (inf[i] == ')') {
            while (!stack1.isEmpty() && stack1.peek() != '(') {
                output += stack1.pop();
                output += ' ';
            }
            stack1.pop();
        } else {
            while (!stack1.isEmpty() && precedence(stack1.peek()) >= precedence(inf[i])) {
                output += stack1.pop();
                output += ' ';
            }
            stack1.push(inf[i]);
        }
    }
    while (!stack1.isEmpty()) {
        output += stack1.pop();
        output += ' ';
    }
    return output;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack2;
    std::string token;
    size_t i = 0;
    while (i < post.length()) {
        if (isspace(post[i])) {
            ++i;
            continue;
        }
        if (isdigit(post[i])) {
            int num = 0;
            while (i < post.length() && isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                ++i;
            }
            stack2.push(num);
        } else {
            int right = stack2.pop();
            int left = stack2.pop();
            switch (post[i]) {
                case '+': stack2.push(left + right); break;
                case '-': stack2.push(left - right); break;
                case '*': stack2.push(left * right); break;
                case '/': stack2.push(left / right); break;
            }
            ++i;
        }
    }
    return stack2.pop();
}
