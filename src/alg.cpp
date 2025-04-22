// Copyright 2025 NNTU-CS

#include <cctype>
#include <cmath>
#include <string>

#include "tstack.h"
int getPriority(char op) {
  switch (op) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  case '^':
    return 3;
  default:
    return 0;
  }
}

std::string infx2pstfx(const std::string &inf) {
  TStack<char, 100> stack;
  std::string postfix;

  for (char c : inf) {
    if (isspace(c))
      continue;

    if (isdigit(c)) {
      postfix += c;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        postfix += ' ';
        postfix += stack.pop();
      }
      stack.pop();
    } else {
      postfix += ' ';
      while (!stack.isEmpty() && getPriority(stack.top()) >= getPriority(c)) {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.push(c);
    }
  }

  while (!stack.isEmpty()) {
    postfix += ' ';
    postfix += stack.pop();
  }

  return postfix;
}

int eval(const std::string &postfix) {
  TStack<int, 100> stack;

  for (size_t i = 0; i < postfix.size();) {
    if (isspace(postfix[i])) {
      i++;
      continue;
    }

    if (isdigit(postfix[i])) {
      int num = 0;
      while (i < postfix.size() && isdigit(postfix[i])) {
        num = num * 10 + (postfix[i] - '0');
        i++;
      }
      stack.push(num);
    } else {
      int b = stack.pop();
      int a = stack.pop();

      switch (postfix[i]) {
      case '+':
        stack.push(a + b);
        break;
      case '-':
        stack.push(a - b);
        break;
      case '*':
        stack.push(a * b);
        break;
      case '/':
        stack.push(a / b);
        break;
      case '^':
        stack.push(pow(a, b));
        break;
      }
      i++;
    }
  }

  return stack.pop();
}
