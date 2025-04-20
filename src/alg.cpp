// Copyright 2025 NNTU-CS
#include <map>
#include <sstream>
#include <string>
#include <cctype>
#include "tstack.h"

int prior(char c) {
  switch (c) {
  case '+': return 1;
  case '-': return 1;
  case '*': return 2;
  case '/': return 2;
  default: return 0;
  }
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> op;
  std::stringstream res;
  std::string num;
  for (char x : inf) {
    if (isdigit(x)) {
      num += x;
    } else if (!num.empty()) {
      res << num << " ";
      num.clear();
    }
    if (x == '(') {
      op.push(x);
    } else if (x == ')') {
      while (!op.isEmpty() && op.top() != '(') {
        res << op.pop() << " ";
      }
      op.pop();
    } else if (x == '+' || x == '-' || x == '*' || x == '/') {
      while (!op.isEmpty() && prior(op.top()) >= prior(x)) {
        res << op.pop() << " ";
      }
      op.push(x);
    }
  }
  if (!num.empty()) {
    res << num << " ";
  }
  while (!op.isEmpty()) {
    res << op.pop() << " ";
  }
  std::string out = res.str();
  if (!out.empty() && out.back() == ' ') {
    out.pop_back();
  }
  return out;
}
int eval(const std::string& post) {
  TStack<int, 100> op;
  std::stringstream in(post);
  std::string f;
  while (in >> f) {
    if (isdigit(f[0])) {
      op.push(std::stoi(f));
    } else {
      int right = op.pop();
      int left = op.pop();
      switch (f[0]) {
      case '+':
        op.push(left + right);
        break;
      case '-':
        op.push(left - right);
        break;
      case '*':
        op.push(left * right);
        break;
      case '/':
        op.push(left / right);
        break;
      }
    }
  }
  return op.pop();
}
