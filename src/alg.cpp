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
  return op_priority.find(c) != op_priority.end() && c != '(';
}
int power(int base, int exp) {
  return (exp > 0) ? base * power(base, exp - 1) : 1;
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
  for (std::size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
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
        stack.Push(c);
      } else if (c == ')') {
        while (!stack.IsEmpty() && stack.Peek() != '(') {
          if (!postfix.empty() && postfix.back() != ' ') postfix.push_back(' ');
          postfix.push_back(stack.Pop());
        }
        if (!stack.IsEmpty()) stack.Pop();
      } else {
        while (!stack.IsEmpty() && priority[stack.Peek()] >= priority[c]) {
          if (!postfix.empty() && postfix.back() != ' ') postfix.push_back(' ');
          postfix.push_back(stack.Pop());
        }
        if (!postfix.empty() && postfix.back() != ' ') postfix.push_back(' ');
        stack.Push(c);
      }
    }
  }
  while (!stack.IsEmpty()) {
    if (!postfix.empty() && postfix.back() != ' ') postfix.push_back(' ');
    postfix.push_back(stack.Pop());
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
        stack.Push(num);
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
        stack.Push(num);
        num = 0;
        readingNum = false;
      }
      int b = stack.Pop();
      int a = stack.Pop();
      if (c == '+') stack.Push(a + b);
      else if (c == '-') stack.Push(a - b);
      else if (c == '*') stack.Push(a * b);
      else if (c == '/') stack.Push(a / b);
      else if (c == '^') stack.Push(power(a, b));
    }
  }
  return stack.Pop();
}
