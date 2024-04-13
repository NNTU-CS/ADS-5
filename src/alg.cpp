// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}
int getPrecedence(char c) {
  if (c == '+' || c == '-') {
    return 1;
  } else if (c == '*' || c == '/') {
    return 2;
  }
  return 0;
}
std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack;
  std::string postfix;
  for (char c : inf) {
    if (c == ' ') {
      continue;
    }
    if (isdigit(c)) {
      postfix += c;
      postfix += ' ';
    } else if (isOperator(c)) {
      while (!stack.isEmpty() && stack.get() != '(' && getPrecedence(c) <= getPrecedence(stack.get())) {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.push(c);
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.pop();
    }
  }
  while (!stack.isEmpty()) {
    postfix += stack.pop();
    postfix += ' ';
  }
  return postfix;
}

int eval(std::string pref) {
  TStack<int, 100> stack;
  for (char c : post) {
    if (c == ' ') {
      continue;
    }
    if (isdigit(c)) {
      stack.push(c - '0');
    } else if (isOperator(c)) {
      int operand2 = stack.pop();
      int operand1 = stack.pop();
      int result;
      switch (c) {
        case '+':
          result = operand1 + operand2;
          break;
        case '-':
          result = operand1 - operand2;
          break;
        case '*':
          result = operand1 * operand2;
          break;
        case '/':
          result = operand1 / operand2;
          break;
      }
      stack.push(result);
    }
  }
  return stack.pop();
}
