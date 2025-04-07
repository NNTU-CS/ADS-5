// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string postfix;
  bool prevWasDigit = false;

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];

    if (c == ' ') continue;

    if (isdigit(c)) {
      if (prevWasDigit) {
        postfix += c;
      } else {
        if (!postfix.empty()) postfix += ' ';
        postfix += c;
        prevWasDigit = true;
      }
    } else {
      prevWasDigit = false;

      if (c == '(') {
        stack.push(c);
      } else if (c == ')') {
        while (!stack.isEmpty() && stack.top() != '(') {
          postfix += ' ';
          postfix += stack.pop();
        }
        stack.pop();
      } else {
        while (!stack.isEmpty() && getPriority(stack.top()) >= getPriority(c)) {
          postfix += ' ';
          postfix += stack.pop();
        }
        stack.push(c);
      }
    }
  }

  while (!stack.isEmpty()) {
    postfix += ' ';
    postfix += stack.pop();
  }

  return postfix;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  int num = 0;
  bool readingNum = false;

  for (size_t i = 0; i < post.size(); ++i) {
    char c = post[i];

    if (isdigit(c)) {
      num = num * 10 + (c - '0');
      readingNum = true;
    } else {
      if (readingNum) {
        stack.push(num);
        num = 0;
        readingNum = false;
      }

      if (c == ' ') continue;

      int right = stack.pop();
      int left = stack.pop();
      switch (c) {
        case '+': stack.push(left + right); break;
        case '-': stack.push(left - right); break;
        case '*': stack.push(left * right); break;
        case '/': stack.push(left / right); break;
      }
    }
  }

  if (readingNum) {
    stack.push(num);
  }

  return stack.pop();
}
