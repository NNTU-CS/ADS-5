// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

int precedence(char oper) {
  if (oper == '+' || oper == '-') return 1;
  if (oper == '*' || oper == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string output;
  bool prevWasDigit = false;

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    if (c == ' ') continue;

    if (isdigit(c)) {
      if (prevWasDigit) {
        output += c;
      }
      else {
        if (!output.empty()) output += ' ';
        output += c;
      }
      prevWasDigit = true;
    }
    else {
      prevWasDigit = false;
      if (c == '(') {
        stack.push(c);
      }
      else if (c == ')') {
        while (!stack.isEmpty() && stack.peek() != '(') {
          output += ' ';
          output += stack.pop();
        }
        stack.pop();
      }
      else {
        while (!stack.isEmpty() && precedence(c) <= precedence(stack.peek())) {
          output += ' ';
          output += stack.pop();
        }
        stack.push(c);
      }
    }
  }

  while (!stack.isEmpty()) {
    output += ' ';
    output += stack.pop();
  }
  return output;
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
    }
    else {
      if (readingNum) {
        stack.push(num);
        num = 0;
        readingNum = false;
      }

      if (c == ' ') continue;

      if (stack.isEmpty()) return 0;
      int b = stack.pop();
      if (stack.isEmpty()) return b;
      int a = stack.pop();
      switch (c) {
      case '+': stack.push(a + b); break;
      case '-': stack.push(a - b); break;
      case '*': stack.push(a * b); break;
      case '/': stack.push(a / b); break;
      }
    }
  }

  if (readingNum) stack.push(num);
  return stack.pop();
}
