// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isOperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

int priority(char op) {
  switch (op) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    default:
      return 0;
  }
}

std::string infx2pstfx(std::string inf) {
  std::string pstfx;
  TStack<char, 100> stack;

  for (char c : inf) {
    if (c == ' ') continue;
    if (isdigit(c)) {
      pstfx += c;
    } else if (isOperator(c)) {
      while (!stack.isEmpty() && priority(stack.get()) >= priority(c)) {
        pstfx += " ";
        pstfx += stack.pop();
      }
      pstfx += " ";
      stack.push(c);
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        pstfx += " ";
        pstfx += stack.pop();
      }
      stack.pop();
    }
  }

  while (!stack.isEmpty()) {
    pstfx += " ";
    pstfx += stack.pop();
  }

  return pstfx;
}

int eval(std::string pref) {
  TStack<int, 100> stack;
  int operand1, operand2;

  for (char c : pref) {
    if (c == ' ') continue;
    if (isdigit(c)) {
      stack.push(c - '0');
    } else if (isOperator(c)) {
      operand2 = stack.pop();
      operand1 = stack.pop();
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
}
