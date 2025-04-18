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

void top2postfix(TStack<char>& stack, std::string& postfix) {
  postfix += stack.top();
  stack.pop();
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string postfix;
  for (char ch : inf) {
    if (isalnum(ch)) {
      postfix += ch;
    } else if (getPriority(ch) == 0) {
      stack.push(ch);
    } else if (getPriority(ch) == 1) {
      while (!stack.isEmpty() && getPriority(stack.top()) != 0) {
        top2postfix(stack, postfix);
      }
      stack.pop();
    } else {
      while (!stack.isEmpty() && getPriority(stack.top()) >= getPriority(ch)) {
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

int eval(const std::string& pref) {
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
