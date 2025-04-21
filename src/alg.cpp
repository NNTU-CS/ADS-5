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
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string postfix = "";
  std::map<char, int> priority;
  priority['+'] = 1;
  priority['-'] = 1;
  priority['*'] = 2;
  priority['/'] = 2;
  int i = 0;
  while (i < inf.length()) {
    char token = inf[i];
    if (isDigit(token)) {
      while (i < inf.length() && isDigit(inf[i])) {
        postfix += inf[i];
        i++;
      }
      postfix += ' ';
      continue;
    } else if (token == '(') {
      stack.push(token);
    } else if (token == ')') {
      char topOp;
      while (!stack.isEmpty() && stack.get() != '(') {
        stack.pop(topOp);
        postfix += topOp;
        postfix += ' ';
      }
      if (!stack.isEmpty()) {
        stack.pop(topOp);
      }
    } else if (isOperator(token)) {
    char topOp;
    while (!stack.isEmpty() && stack.get() != '(' &&
      priority[stack.get()] >= priority[token] && token != '^') {
      stack.pop(topOp);
      postfix += topOp;
      postfix += ' ';
    }
    stack.push(token);
    }
    i++;
  }
  char topOp;
  while (!stack.isEmpty()) {
    stack.pop(topOp);
    postfix += topOp;
    postfix += ' ';
  }
  return postfix;
}
int eval(const std::string& pref) {
  TStack<int, 100> stack;
  int i = 0;
  while (i < post.length()) {
    if (post[i] == ' ') {
      i++;
      continue;
    }
    if (post[i] >= '0' && post[i] <= '9') {
      int num = 0;
      while (i < post.length() && post[i] >= '0' && post[i] <= '9') {
        num = num * 10 + (post[i] - '0');
        i++;
      }
      stack.push(num);
    } else if (isOperator(post[i])) {
      int b, a, result = 0;
      stack.pop(b);
      stack.pop(a);
      switch (post[i]) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
      }
      stack.push(result);
      i++;
    } else {
      i++;
    }
  }
  int finalResult;
  stack.pop(finalResult);
  return finalResult;
}
