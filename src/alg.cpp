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
 std::string post;
    TStack<char, 100> stack;
    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (isspace(c)) continue;
        if (isdigit(c)) {
            while (i < inf.size() && isdigit(inf[i])) 
                post += inf[i++];
            post += ' ';
            i--;
        }
        else if (c == '(') stack.push(c);
        else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                post += stack.pop();
                post += ' ';
            }
            stack.pop();
        }
        else {
            while (!stack.isEmpty() && precedence(stack.top()) >= precedence(c)) {
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
    
    if (!post.empty() && post.back() == ' ') post.pop_back();
    return post;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack;
    for (size_t i = 0; i < post.size(); ++i) {
        char c = post[i];
        if (isspace(c)) continue;
        if (isdigit(c)) {
            int num = 0;
            while (i < post.size() && isdigit(post[i])) 
                num = num * 10 + (post[i++] - '0');
            stack.push(num);
            i--;
        }
        else {
            int val2 = stack.pop();
            int val1 = stack.pop();
            switch (c) {
                case '+': stack.push(val1 + val2); break;
                case '-': stack.push(val1 - val2); break;
                case '*': stack.push(val1 * val2); break;
                case '/': stack.push(val1 / val2); break;
            }
        }
    }
    return stack.pop();
}
