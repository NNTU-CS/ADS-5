// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <stack>
#include <sstream>
#include <iostream>
#include "tstack.h"

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
    std::string postfix;
    TStack<char, 100> stack;

    for (size_t i = 0; i < inf.length(); ++i) {
        if (isspace(inf[i])) continue;

        if (isdigit(inf[i])) {
            if (!postfix.empty() && postfix.back() != ' ') {
                postfix += ' ';
            }
            while (i < inf.length() && isdigit(inf[i])) {
                postfix += inf[i++];
            }
            i--;
        } else if (inf[i] == '(') {
            stack.push(inf[i]);
        } else if (inf[i] == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                postfix += ' ';
                postfix += stack.top();
                stack.pop();
            }
            if (!stack.isEmpty() && stack.top() == '(') {
                stack.pop();
            }
        } else {
            while (!stack.isEmpty() && stack.top() != '(' &&
                   precedence(inf[i]) <= precedence(stack.top())) {
                postfix += ' ';
                postfix += stack.top();
                stack.pop();
            }
            stack.push(inf[i]);
        }
    }

    while (!stack.isEmpty()) {
        postfix += ' ';
        postfix += stack.top();
        stack.pop();
    }

    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;


int eval(const std::string& post) {
  TStack<int, 100> stack2;
  std::istringstream iss(post);
  std::string token;
  while (iss >> token) {
    if (isdigit(token[0])) {
      stack2.push(std::stoi(token));
    } else {
      int right = stack2.top(); stack2.pop();
      int left = stack2.top(); stack2.pop();
      switch (token[0]) {
        case '+': stack2.push(left + right); break;
        case '-': stack2.push(left - right); break;
        case '*': stack2.push(left * right); break;
        case '/': stack2.push(left / right); break;
      }
    }
  }
  return stack2.top();
}

