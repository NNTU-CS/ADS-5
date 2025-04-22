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
  int i = 0;
  while (i < pref.size()) {
    while (pref[i] == ' ') {
      i++;
    }

    if (i < pref.size() && (pref[i] == '+' || pref[i] == '-'
      || pref[i] == '*' || pref[i] == '/')) {
      if (stack.get_top() < 1) {
        exit(1);
      }

      int b = stack.pop();
      int a = stack.pop();

      char symbol = pref[i];
      if (symbol == '+') {
        stack.push(a + b);
      } else if (symbol == '-') {
        stack.push(a - b);
      } else if (symbol == '*') {
        stack.push(a * b);
      } else if (symbol == '/') {
        stack.push(a / b);
      }

      i++;
    } else if (i < pref.size() && isdigit(pref[i])) {
      int num = 0;
      while (i < pref.size() && isdigit(pref[i])) {
        num = num * 10 + (pref[i] - '0');
        i++;
      }

      stack.push(num);
    }
  }

  return stack.get_item();
}
