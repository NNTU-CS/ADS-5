// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string result;
  std::map<char, int> precedence = {
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2},
    {'(', 0}
  };

  for (size_t i = 0; i < inf.length(); ++i) {
    char ch = inf[i];

    if (isspace(ch)) {
      continue;
    }

    if (isdigit(ch)) {
      while (i < inf.length() && isdigit(inf[i])) {
        result += inf[i];
        ++i;
      }
      result += ' ';
      --i;
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        result += stack.pop();
        result += ' ';
      }
      stack.pop();
    } else if (precedence.find(ch) != precedence.end()) {
      while (!stack.isEmpty() && precedence[stack.top()] >= precedence[ch]) {
        result += stack.pop();
        result += ' ';
      }
      stack.push(ch);
    } else {
      throw std::invalid_argument("Invalid character in input");
    }
  }

  while (!stack.isEmpty()) {
    result += stack.pop();
    result += ' ';
  }

  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }

  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;

  for (size_t i = 0; i < post.length(); ++i) {
    char ch = post[i];

    if (isspace(ch)) {
      continue;
    }

    if (isdigit(ch)) {
      int num = 0;
      while (i < post.length() && isdigit(post[i])) {
        num = num * 10 + (post[i] - '0');
        ++i;
      }
      stack.push(num);
      --i;
    } else {
      if (stack.isEmpty()) {
        throw std::runtime_error("Insufficient operands in postfix expression");
      }
      int b = stack.pop();
      if (stack.isEmpty()) {
        throw std::runtime_error("Insufficient operands in postfix expression");
      }
      int a = stack.pop();

      switch (ch) {
        case '+': stack.push(a + b); break;
        case '-': stack.push(a - b); break;
        case '*': stack.push(a * b); break;
        case '/':
          if (b == 0) {
            throw std::runtime_error("Division by zero");
          }
          stack.push(a / b);
          break;
        default: throw std::invalid_argument("Invalid operator");
      }
    }
  }

  if (stack.isEmpty()) {
    throw std::runtime_error("Empty stack after evaluation");
  }

  return stack.pop();
}
