// Copyright 2025 NNTU-CS
#include <string>
#include <stack>
#include <cctype>
#include <map>
#include "tstack.h"

int getPriority(char op) {
  switch (op) {
    case '(': return 0;
    case ')': return 1;
    case '+': case '-': return 2;
    case '*': case '/': return 3;
    default: return -1;
  }
}

void top2pstfx(TStack<char, 100>& stack,
std::string& postfix) {
  if (!postfix.empty() && postfix.back() != ' ') {
    postfix += ' ';
  }
  postfix += stack.getTop();
  stack.pop();
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string postfix;
  bool needSpace = false;
  for (char ch : inf) {
    if (isdigit(ch)) {
      if (needSpace) {
        postfix += ' ';
        needSpace = false;
      }
      postfix += ch;
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.isEmpty() && stack.getTop() != '(') {
        top2pstfx(stack, postfix);
      }
      if (!stack.isEmpty()) {
        stack.pop();
      }
    } else if (getPriority(ch) > 1) {
      while (!stack.isEmpty() &&
        getPriority(stack.getTop()) >= getPriority(ch)) {
        top2pstfx(stack, postfix);
      }
      stack.push(ch);
      needSpace = true;
    }
  }
  while (!stack.isEmpty()) {
    top2pstfx(stack, postfix);
  }
  return postfix;
}

int eval(const std::string& postfix) {
  std::stack<int> stack;
  std::string token;
  for (char ch : postfix) {
    if (ch == ' ') {
      if (!token.empty()) {
        stack.push(std::stoi(token));
        token.clear();
      }
      continue;
    }
    if (isdigit(ch)) {
      token += ch;
    } else {
      if (!token.empty()) {
        stack.push(std::stoi(token));
        token.clear();
      }
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
