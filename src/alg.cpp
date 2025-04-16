// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include "tstack.h"

static int GetPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::stringstream postfix;
  bool prev_was_digit = false;

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];

    if (isspace(c)) {
      continue;
    }

    if (isdigit(c)) {
      if (prev_was_digit) {
        postfix << c;
      } else {
        if (i != 0) {
          postfix << ' ';
        }
        postfix << c;
      }
      prev_was_digit = true;
    } else {
      prev_was_digit = false;

      if (c == '(') {
        stack.push(c);
      } else if (c == ')') {
        while (!stack.empty() && stack.top() != '(') {
          postfix << ' ' << stack.pop();
        }
        stack.pop();
      } else {
        while (!stack.empty() &&
               GetPriority(stack.top()) >= GetPriority(c)) {
          postfix << ' ' << stack.pop();
        }
        stack.push(c);
      }
    }
  }

  while (!stack.empty()) {
    postfix << ' ' << stack.pop();
  }

  return postfix.str();
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::stringstream ss(post);
  std::string token;

  while (ss >> token) {
    if (isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else {
      int right = stack.pop();
      int left = stack.pop();

      switch (token[0]) {
        case '+':
          stack.push(left + right);
          break;
        case '-':
          stack.push(left - right);
          break;
        case '*':
          stack.push(left * right);
          break;
        case '/':
          stack.push(left / right);
          break;
      }
    }
  }

  return stack.pop();
}
