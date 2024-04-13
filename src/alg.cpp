#include <iostream>
#include <stack>
#include <string>
#include "include/tstack.h"
bool isOperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}
int precedence(char op) {
  if (op == '+' || op == '-') {
    return 1;
  } else if (op == '*' || op == '/') {
    return 2;
  }
  return 0;
}
std::string infx2pstfx(std::string inf) {
  std::string post = "";
  TStack<char, 100> stack;
  for (char c : inf) {
    if (c == ' ') {
      continue;
    } else if (isdigit(c)) {
      post += c;
      post += ' ';
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        post += stack.get();
        post += ' ';
        stack.pop();
      }
      stack.pop();
    } else if (isOperator(c)) {
      while (!stack.isEmpty() && precedence(stack.get()) >= precedence(c)) {
        post += stack.get();
        post += ' ';
        stack.pop();
      }
      stack.push(c);
    }
  }
  while (!stack.isEmpty()) {
    post += stack.get();
    post += ' ';
    stack.pop();
  }
  return post;
}
int performOperation(int operand1, int operand2, char op) {
  switch(op) {
    case '+':
      return operand1 + operand2;
    case '-':
      return operand1 - operand2;
    case '*':
      return operand1 * operand2;
    case '/':
      return operand1 / operand2;
    default:
      return 0;
  }
}
int eval(std::string post) {
  TStack<int, 100> stack;
  for (char c : post) {
    if (c == ' ') {
      continue;
    } else if (isdigit(c)) {
      int operand = 0;
      while (isdigit(c)) {
        operand = operand * 10 + (c - '0');
        c = *(&c + 1);
      }
      stack.push(operand);
    } else if (isOperator(c)) {
      int operand2 = stack.get();
      stack.pop();
      int operand1 = stack.get();
      stack.pop();
      int result = performOperation(operand1, operand2, c);
      stack.push(result);
    }
  }
  return stack.get();
}
