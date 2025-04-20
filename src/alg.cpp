// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include <map>
#include "tstack.h"

int GetPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string result;
  std::string number;

  for (char c : inf) {
    if (isdigit(c)) {
      number += c;
    } else {
      if (!number.empty()) {
        result += number + ' ';
        number.clear();
      }

      if (c == '(') {
        stack.Push(c);
      } else if (c == ')') {
        while (!stack.IsEmpty() && stack.Top() != '(') {
          result += stack.Pop();
          result += ' ';
        }
        if (!stack.IsEmpty()) {
          stack.Pop();  // Убираем '('
        }
      } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        while (!stack.IsEmpty() && GetPriority(stack.Top()) >= GetPriority(c)) {
          result += stack.Pop();
          result += ' ';
        }
        stack.Push(c);
      }
    }
  }

  if (!number.empty()) {
    result += number + ' ';
  }

  while (!stack.IsEmpty()) {
    result += stack.Pop();
    result += ' ';
  }

  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }

  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::string number;

  for (size_t i = 0; i < post.size(); ++i) {
    char c = post[i];
    if (isdigit(c)) {
      number += c;
    } else if (c == ' ' && !number.empty()) {
      stack.Push(std::stoi(number));
      number.clear();
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      int b = stack.Pop();
      int a = stack.Pop();
      int res = 0;
      switch (c) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = a / b; break;
      }
      stack.Push(res);
    }
  }

  if (!number.empty()) {
    stack.Push(std::stoi(number));
  }

  return stack.Pop();
}
