// Copyright 2025 NNTU-CS
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include "tstack.h"

const int kStackSize = 100;
int priority(char c) {
  if (c == '+' || c == '-') return 1;
  if (c == '*' || c == '/') return 2;
  return 0;
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, kStackSize> operators;
  std::ostringstream out;
  for (size_t i = 0; i < inf.length(); ++i) {
    char current = inf[i];
    if (current == ' ') continue;
    if (isdigit(current)) {
      while (i < inf.length() && isdigit(inf[i])) {
        out << inf[i++];
      }
      out << ' ';
      --i;
    } else if (current == '(') {
      operators.push(current);
    } else if (current == ')') {
      while (!operators.isEmpty() && operators.top() != '(') {
        out << operators.top() << ' ';
        operators.pop();
      }
      operators.pop();
    } else {
      while (!operators.isEmpty() && priority(operators.top()) >= priority(current)) {
        out << operators.top() << ' ';
        operators.pop();
      }
      operators.push(current);
    }
  }
  while (!operators.isEmpty()) {
    out << operators.top() << ' ';
    operators.pop();
  }
  return out.str();
}
int eval(const std::string& post) {
  TStack<int, kStackSize> operands;
  std::istringstream input(post);
  std::string token;
  while (input >> token) {
    if (isdigit(token[0])) {
      operands.push(std::stoi(token));
    } else {
      int right = operands.top();
      operands.pop();
      int left = operands.top();
      operands.pop();
      switch (token[0]) {
      case '+':
        operands.push(left + right);
        break;
      case '-':
        operands.push(left - right);
        break;
      case '*':
        operands.push(left * right);
        break;
      case '/':
        operands.push(left / right);
        break;
      }
    }
  }
  return operands.top();
}
