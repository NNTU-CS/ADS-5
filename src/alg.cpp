// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}
int getPriority(char op) {
  switch (op) {
  case '(':
    return 0;
  case '+': case '-':
    return 1;
  case '*': case '/':
    return 2;
  default:
    return -1;
  }
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string postfix;
  bool flag = false;
  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    if (c >= '0' && c <= '9') {
      if (flag) {
        postfix += c;
      } else {
        if (!postfix.empty())
          postfix += ' ';
        postfix += c;
      }
      flag = true;
    } else if (c == '(') {
      stack.push(c);
      flag = false;
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        postfix += ' ';
        postfix += stack.get();
        stack.pop();
      }
      if (!stack.isEmpty()) stack.pop();
      flag = false;
    } else if (isOperator(c)) {
      while (!stack.isEmpty() && getPriority(stack.get()) >= getPriority(c)) {
        postfix += ' ';
        postfix += stack.get();
        stack.pop();
      }
      stack.push(c);
      flag = false;
    }
  }
  while (!stack.isEmpty()) {
    postfix += ' ';
    postfix += stack.get();
    stack.pop();
  }
  return postfix;
}
int eval(const std::string& pref) {
  TStack<int, 100> stack;
  int num = 0;
  bool flag = false;
  for (size_t i = 0; i < pref.size(); ++i) {
    char c = pref[i];
    if (c >= '0' && c <= '9') {
      num = num * 10 + (c - '0');
      flag = true;
    } else if (c == ' ') {
      if (flag) {
        stack.push(num);
        num = 0;
        flag = false;
      }
    } else if (isOperator(c)) {
      int op2 = stack.get();
      stack.pop();
      int op1 = stack.get();
      stack.pop();
      switch (c) {
      case '+':
        stack.push(op1 + op2);
        break;
      case '-':
        stack.push(op1 - op2);
        break;
      case '*':
        stack.push(op1 * op2);
        break;
      case '/':
        stack.push(op1 / op2);
        break;
      }
    }
  }
  return stack.get();
}
