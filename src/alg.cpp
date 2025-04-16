// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int applyOp(int a, int b, char op) {
  switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: throw std::invalid_argument("Unknown operator");
  }
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream in(post);
  std::string token;
  while (in >> token) {
    if (isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else {
      if (stack.size() < 2) {
        throw std::runtime_error("Invalid expression");
      }
      int b = stack.get();
      stack.pop();
      int a = stack.get();
      stack.pop();
      stack.push(applyOp(a, b, token[0]));
    }
  }
  if (stack.size() != 1) {
    throw std::runtime_error("Invalid expression");
  }
  return stack.get();
}

int priority(char op) {
  if (op == '*' || op == '/') return 2;
  if (op == '+' || op == '-') return 1;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::ostringstream out;
  for (size_t i = 0; i < inf.length(); ++i) {
    if (isspace(inf[i])) continue;
    if (isdigit(inf[i])) {
      while (i < inf.length() && isdigit(inf[i])) {
        out << inf[i++];
      }
      out << ' ';
      --i;
    } else if (inf[i] == '(') {
      stack.push(inf[i]);
    } else if (inf[i] == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        out << stack.get() << ' ';
        stack.pop();
      }
      if (!stack.isEmpty()) stack.pop();
    } else {
      while (!stack.isEmpty() &&
             priority(stack.get()) >= priority(inf[i])) {
        out << stack.get() << ' ';
        stack.pop();
      }
      stack.push(inf[i]);
    }
  }
  while (!stack.isEmpty()) {
    out << stack.get() << ' ';
    stack.pop();
  }
  return out.str();
}
