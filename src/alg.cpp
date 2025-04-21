// Copyright 2025 NNTU-CS
#include <cctype>
#include <map>
#include <string>
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
  int res = 1;
  for (int i = 0; i < exp; ++i) res *= base;
  return res;
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
    if (isDigit(c)) {
      if (prevWasDigit) postfix.push_back(c);
      else {
        if (!postfix.empty() && postfix.back() != ' ') postfix.push_back(' ');
        postfix.push_back(c);
      }
      prevWasDigit = true;
    } else {
      if (prevWasDigit) {
        postfix.push_back(' ');
        prevWasDigit = false;
      }
      if (c == '(') {
        stack.push(c);
      } else if (c == ')') {
        while (!stack.empty() && stack.Top() != '(') {
          if (!postfix.empty() && postfix.back() != ' ') postfix.push_back(' ');
          postfix.push_back(stack.pop());
        }
        if (!stack.empty()) stack.pop();
      } else {
        while (!stack.empty() && priority[stack.Top()] >= priority[c]) {
          if (!postfix.empty() && postfix.back() != ' ') postfix.push_back(' ');
          postfix.push_back(stack.pop());
        }
        if (!postfix.empty() && postfix.back() != ' ') postfix.push_back(' ');
        stack.push(c);
      }
    }
  }
  while (!stack.empty()) {
    if (!postfix.empty() && postfix.back() != ' ') postfix.push_back(' ');
    postfix.push_back(stack.pop());
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
    if (isDigit(c)) {
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
      if (c == '+') stack.push(a + b);
      else if (c == '-') stack.push(a - b);
      else if (c == '*') stack.push(a * b);
      else if (c == '/') stack.push(a / b);
      else if (c == '^') stack.push(power(a, b));
    }
  }
  return stack.pop();
}
