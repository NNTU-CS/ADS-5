// Copyright 2021 NNTU-CS
#include "tstack.h"
#include <string>
#include <map>

int getPriority(char operand) {
  if (operand == '+' || operand == '-') return 1;
  if (operand == '*' || operand == '/') return 2;

  return 0;
}

std::string infx2pstfx(std::string inf) {
  TStack<char> stack;
  std::string postfix;

  for (char c : inf) {
    if (isdigit(c)) {
      postfix += c + ' ';
    } else if (c == '(') {
      stack.push(c);
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!stack.isEmpty() && getPriority(stack.show()) >= getPriority(c)) {
        postfix += stack.pop() + ' ';
      }

      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.show() != '(') {
        postfix += stack.pop() + ' ';
      }

      stack.pop();
    }
  }

  while (!stack.isEmpty()) {
    postfix += stack.pop() + ' ';
  }

  if (!postfix.empty()) {
    postfix.pop_back();
  }

  return postfix;
}

int eval(std::string pref) {
  TStack<int> stack;
  std::string buffer = "";

  for (char c : pref) {
    if (isdigit(c)) {
      buffer += c;
    }

    if (c == ' ') {
      if (!buffer.empty()) {
        int num = std::stoi(buffer);
        stack.push(num);
        buffer = "";
      }
    }

    if (c == '+' || c == '-' || c == '*' || c == '/') {
      int b = stack.pop();
      int a = stack.pop();

      switch (c) {
        case '+':
          stack.push((a + b));
        case '-':
          stack.push((a - b));
        case '*':
          stack.push((a * b));
        case '/':
          stack.push((a / b));
      }
    }
  }

  return stack.pop();
}
