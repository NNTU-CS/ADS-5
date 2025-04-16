// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

static int getPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::stringstream postfix;
  bool prevWasDigit = false;

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];

    if (isspace(c)) {
      continue;
    }

    if (isdigit(c)) {
      if (prevWasDigit) {
        postfix << c;
      } else {
        if (i != 0) postfix << ' ';
        postfix << c;
      }
      prevWasDigit = true;
    } else {
      prevWasDigit = false;

      if (c == '(') {
        stack.push(c);
      } else if (c == ')') {
        while (!stack.isEmpty() && stack.peek() != '(') {
          postfix << ' ' << stack.pop();
        }
        stack.pop(); // Remove '(' from stack
      } else {
        while (!stack.isEmpty() && getPriority(stack.peek()) >= getPriority(c)) {
          postfix << ' ' << stack.pop();
        }
        stack.push(c);
      }
    }
  }

  while (!stack.isEmpty()) {
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
        case '+': stack.push(left + right); break;
        case '-': stack.push(left - right); break;
        case '*': stack.push(left * right); break;
        case '/': stack.push(left / right); break;
      }
    }
  }

  return stack.pop();
}
