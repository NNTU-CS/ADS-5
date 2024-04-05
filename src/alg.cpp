// Copyright 2021 NNTU-CS
#include <map>
#include "tstack.h"

bool isOp(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

int prec(char c) {
  if (c == '+' || c == '-') {
    return 1;
  } else if (c == '*' || c == '/') {
    return 2;
  }
  return 0;
}

std::string infx2pstfx(std::string inf) {
    std::string postfix;
    TStack<char, 100> stack;
    for (char c : inf) {
        if (isdigit(c)) {
            postfix = postfix + c + ' ';
        } else if (c == '(') {
            stack.push(c);
        } else if (isOp(c)) {
          while (!stack.isEmpty() && prec(stack.get()) >= prec(c)) {
            postfix = postfix + stack.get() + ' ';
            stack.pop();
          }
          stack.push(c);
        } else if (c == ')') {
          while (!stack.isEmpty() && stack.get() != '(') {
            postfix = postfix + stack.get() + ' ';
            stack.pop();
          }
          stack.pop();
        }
    }
    while (!stack.isEmpty()) {
        postfix = postfix + stack.get() + ' ';
        stack.pop();
    }
    if (!postfix.empty()) {
        postfix.pop_back();
    }
    return postfix;
}

int eval(std::string post) {
  TStack<int, 100> stack;
  for (char c : post) {
    if (std::isdigit(c)) {
      stack.push(c - '0');
    } else if (isOp(c)) {
      int operand2 = stack.pop();
      int operand1 = stack.pop();
      switch (c) {
        case '+':
          stack.push(operand1 + operand2);
          break;
        case '-':
          stack.push(operand1 - operand2);
          break;
        case '*':
          stack.push(operand1 * operand2);
          break;
        case '/':
          stack.push(operand1 / operand2);
          break;
      }
    }
  }
  return stack.pop();
  return 0;
}
