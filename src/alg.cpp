// Copyright 2025 NNTU-CS
#include <string>
#include <stack>
#include <cctype>
#include <map>
#include "tstack.h"

void top2postfix(TStack<char, 100>& stack,
std::string& postfix) {
  postfix += stack.getTop();
  stack.pop();
}

int getPriority(char op) {
  switch (op) {
    case '(': return 0;
    case ')': return 1;
    case '+': case '-': return 2;
    case '*': case '/': return 3;
    default: return -1;
  }
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string postfix;
  for (char ch : inf) {
    if (isalnum(ch)) {
      postfix += ch;
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.isEmpty() && stack.getTop() != '(') {
        top2postfix(stack, postfix);
      }
      if (!stack.isEmpty()) {
        stack.pop();
      }
    } else {
      while (!stack.isEmpty() &&
        getPriority(stack.getTop()) >= getPriority(ch)) {
        top2postfix(stack, postfix);
      }
      stack.push(ch);
    }
  }
  while (!stack.isEmpty()) {
    top2postfix(stack, postfix);
  }
  return postfix;
}

int eval(const std::string& postfix) {
  std::stack<int> stack;
  for (char ch : postfix) {
    if (isdigit(ch)) {
      stack.push(ch - '0');
    } else {
      int b = stack.top();
      stack.pop();
      int a = stack.top();
      stack.pop();
      switch (ch) {
        case '+': stack.push(a + b); break;
        case '-': stack.push(a - b); break;
        case '*': stack.push(a * b); break;
        case '/': stack.push(a / b); break;
      }
    }
  }
  return stack.top();
}
