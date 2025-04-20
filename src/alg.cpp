// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
std::map<char, int> op_priority = {
    {'^', 4},
    {'*', 3}, {'/', 3},
    {'+', 2}, {'-', 2},
    {'(', 1}
};
bool isDigit(char c) {
  return c >= '0' && c <= '9';
}
bool isOperator(char c) {
  return op_priority.count(c) && c != '(';
}
int power(int base, int exp) {
  int result = 1;
  for (int i = 0; i < exp; ++i) {
    result *= base;
  }
  return result;
}
std::string infx2pstfx(const std::string& inf) {
  std::map<char, int> priority = {
      {'(', 0},
      {'+', 1}, {'-', 1},
      {'*', 2}, {'/', 2},
      {'^', 3}
  };
  TStack<char, 100> stack;
  std::string postfix;
  bool prevWasDigit = false;
  for (char c : inf) {
    if (c == ' ') continue;
    if (isdigit(c)) {
      if (prevWasDigit) {
        postfix += c;
      } else {
        if (!postfix.empty() && postfix.back() != ' ') {
          postfix += ' ';
        }
        postfix += c;
      }
      prevWasDigit = true;
    } else {
      if (prevWasDigit) {
        postfix += ' ';
        prevWasDigit = false;
      }
      if (c == '(') {
        stack.push(c);
      } else if (c == ')') {
        while (!stack.empty() && stack.Top() != '(') {
          if (!postfix.empty() && postfix.back() != ' ') {
            postfix += ' ';
          }
          postfix += stack.pop();
        }
        stack.pop();
      } else {
        while (!stack.empty() && priority[stack.Top()] >= priority[c]) {
          if (!postfix.empty() && postfix.back() != ' ') {
            postfix += ' ';
          }
          postfix += stack.pop();
        }
        if (!postfix.empty() && postfix.back() != ' ') {
          postfix += ' ';
        }
        stack.push(c);
      }
    }
  }
  while (!stack.empty()) {
    if (!postfix.empty() && postfix.back() != ' ') {
      postfix += ' ';
    }
    postfix += stack.pop();
  }
  
  return postfix;
}
int eval(const std::string& pref) {
  TStack<int, 100> stack;
  int num = 0;
  bool readingNum = false;
  for (char c : pref) {
    if (c == ' ') {
      if (readingNum) {
        stack.push(num);
        num = 0;
        readingNum = false;
      }
      continue;
    }
    if (isdigit(c)) {
      num = num * 10 + (c - '0');
      readingNum = true;
    } else {
      if (readingNum) {
        stack.push(num);
        num = 0;
        readingNum = false;
      }
      int b = stack.pop();
      int a = stack.pop();
      switch (c) {
      case '+': stack.push(a + b); break;
      case '-': stack.push(a - b); break;
      case '*': stack.push(a * b); break;
      case '/': stack.push(a / b); break;
      case '^': {
        int res = 1;
        for (int i = 0; i < b; ++i) res *= a;
        stack.push(res);
        break;
      }
      }
    }
  }
  return stack.pop();
}
