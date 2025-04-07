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
        stack.Push(c);
      } else if (c == ')') {
        while (!stack.IsEmpty() && stack.Top() != '(') {
          postfix += ' ';
          postfix += stack.Pop();
        }
        stack.Pop();
      } else {
        while (!stack.IsEmpty() && getPriority(stack.Top()) >= getPriority(c)) {
          postfix += ' ';
          postfix += stack.Pop();
        }
        stack.Push(c);
      }
    }
  }

  while (!stack.IsEmpty()) {
    postfix += ' ';
    postfix += stack.Pop();
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
        stack.Push(num);
        num = 0;
        readingNum = false;
      }

      if (c == ' ') continue;

      int right = stack.Pop();
      int left = stack.Pop();
      switch (c) {
        case '+': stack.Push(left + right); break;
        case '-': stack.Push(left - right); break;
        case '*': stack.Push(left * right); break;
        case '/': stack.Push(left / right); break;
      }
    }
  }

  if (readingNum) {
    stack.Push(num);
  }

  return stack.Pop();
}
