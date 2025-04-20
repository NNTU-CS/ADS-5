// Copyright 2025 NNTU-CS
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <map>
#include "tstack.h"
int priority(char c) {
  if (c == '+' || c == '-') return 1;
  if (c == '*' || c == '/') return 2;
  return 0;
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> operators;
  std::string out;
  std::istringstream stream(inf);
  std::string x;

  while (stream >> x) {
    if (isdigit(x[0])) {
      out += x + " ";
    }else if (x == "(") {
      operators.push('(');
    }else if (x == ")") {
      while (!operators.isEmpty() && operators.topItem() != '(') {
        out += operators.topItem() + " ";
        operators.pop();
      }
      operators.pop();
    }else {
      while (!operators.isEmpty() && priority(operators.topItem()) >= priority(x[0])) {
        out += operators.topItem() + " ";
        operators.pop();
      }
      operators.push(x[0]);
    }
  }

  while (!operators.isEmpty()) {
    out += operators.topItem() + " ";
    operators.pop();
  }
  return out;;
}

int eval(const std::string& post) {
  TStack<int, 100> values;
  std::istringstream stream(post);
  std::string x;

  while (stream >> x) {
    if (isdigit(x[0])) {
      values.push(std::stoi(x));
    }
    else {
      int right = values.topItem(); values.pop();
      int left = values.topItem(); values.pop();
      switch (x[0]) {
      case '+': values.push(left + right); break;
      case '-': values.push(left - right); break;
      case '*': values.push(left * right); break;
      case '/': values.push(left / right); break;
      }
    }
  }
  return values.topItem();
}
