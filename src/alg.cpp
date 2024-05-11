// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  // добавьте код
  return std::string("");
  bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
  }
  int precedence (char op) {
    if (op == '+' || op == '-')
      return 1;
    if (op == '*' || op == '/')
      return 2;
    return 0;
  }
  std::string infx2pstfx(std::string inf) {
    TStack < char, 100 > stack;
    std::string post;
    for (char c : inf) {
      if (c == ' ') continue;
      if (isdigit(c)) {
        post += c;
      } else if (c == '(') {
        stack.push(c);
      } else if (c == ')') {
        while (!stack.isEmpty() && stack.get() != '(') {
          post += ' ';
          post += stack.pop();
        }
        stack.pop();
      } else if (isOperator(c)) {
        post += ' ';
        while (!stack.isEmpty() && precedence(stack.get()) >= precedence(c)) {
          post += stack.pop();
        }
        stack.push(c);
      }
    }
    while (!stack.isEmpty()) {
      post += ' ';
      post += stack.pop();
    }
    return post;
}

int eval(std::string pref) {
  // добавьте код
  return 0;
  TStack < int, 100 > stack;
  for (char c : post) {
    if (c == ' ') continue;
    if (isdigit(c)) {
      int operand = 0;
      while (isdigit(c)) {
        int i = 0;
        operand = operand * 10 + (c - '0');
        c = post[++i];
      }
      stack.push(operand);
    } else if (isOperator(c)) {
      int operand2 = stack.pop();
      int operand1 = stack.pop();
      switch (c) {
        case '+': stack.push(operand1 + operand2);
        break;
        case '-': stack.push(operand1 - operand2);
        break;
        case '*': stack.push(operand1 * operand2);
        break;
        case '/': stack.push(operand1 / operand2);
        break;
      }
    }
  }
  return stack.pop();
}
