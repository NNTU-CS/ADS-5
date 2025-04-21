// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isDigit(char c) {
  return c >= '0' && c <= '9';
}
bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}
int useOp(int a, int b, char op) {
  switch (op) {
  case '+': return a + b;
  case '-': return a - b;
  case '*': return a * b;
  case '/': return a / b;
  }
  return 0;
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string postfix = "";
  std::map<char, int> priority;
  priority['+'] = 1;
  priority['-'] = 1;
  priority['*'] = 2;
  priority['/'] = 2;
  for (size_t i = 0; i < inf.size(); i++) {
    char ch = inf[i];
    if (isDigit(ch)) {
      postfix += ch;
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        postfix += ' ';
        postfix += stack.pop();
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (priority(ch) > 0) {
      postfix += ' ';
      while (!stack.isEmpty() && priority(stack.get()) >= priority(ch)) {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.push(ch);
    }
  }
  while (!stack.isEmpty()) {
  postfix += ' ';
  postfix += stack.pop();
  }
  return out;
}
int eval(const std::string& pref) {
  TStack<int, 100> stack;
  for (size_t i = 0; i < pref.length(); i++) {
    if (isspace(pref[i])) continue;
    if (isdigit(pref[i])) {
      stack.push(pref[i] - '0');
    } else if (isOperator(pref[i])) {
      int b, a;
      stack.pop(b);
      stack.pop(a);
      int result = useOp(a, b, pref[i]);
      stack.push(result);
    }
  }
  int finalResult;
  stack.pop(finalResult);
  return finalResult;
}
