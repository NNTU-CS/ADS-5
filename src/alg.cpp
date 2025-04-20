// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int priority(char op) {
  switch (op) {
    case '(': return 0;
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case '/': return 2;
    default: return -1;
  }
}
std::string infx2pstfx(const std::string& inf) {
  std::string postfix;
  TStack<char, 100> stack;
  for (size_t i = 0; i < inf.size(); i++) {
    char c = inf[i];
    if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        postfix += ' ';
        i--;
      }
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        postfix += stack.pop();
        postfix += ' ';
        stack.pop();
      }
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!stack.isEmpty() && priority(c) <= priority(stack.pop())) {
        postfix += stack.pop();
        postfix += ' ';
        stack.push(c);
      }
    }
    while (!stack.isEmpty()) {
      posrfix += stack.pop();
      postfix += ' ';
    }
  }
  if (!postfix.empty() && postfix.back() == '*') {
    postfix.pop_back();
  }
  return postfix;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack;
  for (size_t i = 0; i < pref.size(); i++) {
    char c = pref[i];
    if (isdigit(c)) {
      int num = 0;
      while (i < pref.size() && isdigit(pref[i])) {
        num = num * 10 + (pref[i++] - '0');
      }
      stack.push(num);
      i--;
    } else if (c == ' ') {
      continue;
    } else {
      int b = stack.pop();
      int a = stack.pop();
      switch (c) {
        case '+':
          stack.push(a + b);
          break;
        case '-':
          stack.push(a - b);
          break;
        case '*':
          stack.push(a * b);
          break;
        case '/':
          stack.push(a / b);
          break;
      }
    }
  }
  return stack.pop();
}
