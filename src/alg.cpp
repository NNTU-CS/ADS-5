// Copyright 2021 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int priority(char op) {
  if (op == '*' || op == '/') return 2;
  if (op == '+' || op == '-') return 1;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  std::string out;
  TStack<char, 100> stack;

  for (size_t i = 0; i < inf.size(); i++) {
    char ch = inf[i];

    if (isdigit(ch)) {
      out += ch;
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.isEmpty() && stack.getTop() != '(') {
        out += ' ';
        out += stack.pop();
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (priority(ch) > 0) {
      out += ' ';
      while (!stack.isEmpty() && priority(stack.getTop()) >= priority(ch)) {
        out += stack.pop();
        out += ' ';
      }
      stack.push(ch);
    }
  }

  while (!stack.isEmpty()) {
    out += ' ';
    out += stack.pop();
  }

  return out;
}

int eval(const std::string& post) {
  std::istringstream iss(post);
  std::string token;
  TStack<int, 100> stack;

  while (iss >> token) {
    if (isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else {
      int b = stack.pop();
      int a = stack.pop();
      switch (token[0]) {
        case '+': stack.push(a + b); break;
        case '-': stack.push(a - b); break;
        case '*': stack.push(a * b); break;
        case '/': stack.push(a / b); break;
      }
    }
  }

  return stack.pop();
}
