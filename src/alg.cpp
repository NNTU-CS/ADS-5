// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}
std::string infx2pstfx(const std::string& inf) {
  std::ostringstream out;
  TStack<char, 100> stack;
  size_t i = 0;
  while (i < inf.length()) {
    if (isspace(inf[i])) {
      ++i;
      continue;
    }
    if (isdigit(inf[i])) {
      while (i < inf.length() && isdigit(inf[i])) {
        out << inf[i++];
      }
      out << ' ';
    } else if (inf[i] == '(') {
      stack.push(inf[i]);
      ++i;
    } else if (inf[i] == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        out << stack.get() << ' ';
        stack.pop();
      }
      if (!stack.isEmpty()) {
        stack.pop();
      }
      ++i;
    } else {
      while (!stack.isEmpty() && priority(stack.get()) >= priority(inf[i])) {
        out << stack.get() << ' ';
        stack.pop();
      }
      stack.push(inf[i]);
      ++i;
    }
  }
  while (!stack.isEmpty()) {
    out << stack.get() << ' ';
    stack.pop();
  }
  std::string result = out.str();
  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
  return result;
}
int applyOp(int a, int b, char op) {
  switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: throw "Unknown operator";
  }
}
int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream in(post);
  std::string token;
  while (in >> token) {
    if (isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else if (token.length() == 1 && std::string("+-*/").find(token[0]) != std::string::npos) {
      int b = stack.get();
      stack.pop();
      int a = stack.get();
      stack.pop();
      int res = applyOp(a, b, token[0]);
      stack.push(res);
    } else {
      throw "Invalid token in expression";
    }
  }
  if (stack.size() != 1) {
    throw "Invalid expression";
  }
  return stack.get();
}
