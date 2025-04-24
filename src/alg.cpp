// Copyright 2025 NNTU-CS
#include <ctype.h>
#include <iostream>
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  std::string res = "";
  TStack<char, 100> stack;
  std::string current_number = "";
  for (char c : inf) {
    if (isdigit(c)) {
      current_number += c;
      continue;
    } else {
      if (!current_number.empty()) {
        res += current_number;
        res += ' ';
        current_number = "";
      }
    }

    if (c == '(') {
      stack.push(c);
    } else if (c == '*' || c == '/') {
      if (stack.get_top() == -1) {
        stack.push(c);
        continue;
      }

      if (stack.get_item() == '*' || stack.get_item() == '/') {
        while (stack.get_item() == '*' || stack.get_item() == '/') {
          res += stack.pop();
          res += ' ';
        }

        if (stack.get_top() != -1 && stack.get_item() == '(') {
          stack.pop();
        }
      }

      stack.push(c);
    } else if (c == '-' || c == '+') {
      if (stack.get_top() == -1) {
        stack.push(c);
        continue;
      }

      if (stack.get_item() == '-' || stack.get_item() == '+' ||
        stack.get_item() == '*' || stack.get_item() == '/') {
        while (stack.get_item() == '-' || stack.get_item() == '+' ||
          stack.get_item() == '*' || stack.get_item() == '/') {
          res += stack.pop();
          res += ' ';
        }

        if (stack.get_top() != -1 && stack.get_item() == '(') {
          stack.pop();
        }
      }

      stack.push(c);
    } else if (c == ')') {
      while (stack.get_top() != -1 && stack.get_item() != '(') {
        res += stack.pop();
        res += ' ';
      }

      stack.pop();
    }
  }

  if (!current_number.empty()) {
    res += current_number;
    res += ' ';
  }

  while (stack.get_top() != -1) {
    res += stack.pop();
    res += ' ';
  }

  res.pop_back();

  return res;
}

int eval(const std::string& pref) {
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
