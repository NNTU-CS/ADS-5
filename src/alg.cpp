// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::map<char, int> op = {
    {'^', 4},
    {'*', 3}, {'/', 3},
    {'+', 2}, {'-', 2},
    {'(', 1}
};

bool isOperator(char c) {
  return op.count(c) && c != '(';
}
bool isDigit(char c) {
  return c >= '0' && c <= '9';
}
int power(int base, int exp) {
  int res = 1;
  for (int i = 0; i < exp; ++i) {
    res = res * base;
  }
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
    if (isdigit(c)) {
      if (prevWasDigit) {
        postfix = postfix + c;
      } else {
        if (!postfix.empty() && postfix.back() != ' ') {
          postfix = postfix + ' ';
        }
        postfix = postfix + c;
      }
      prevWasDigit = true;
    } else {
      if (prevWasDigit) {
        postfix = postfix + ' ';
        prevWasDigit = false;
      }
      if (c == '(') {
        stack.push(c);
      } else if (c == ')') {
        while (!stack.empty() && stack.Top() != '(') {
          if (!postfix.empty() && postfix.back() != ' ') {
            postfix = postfix + ' ';
          }
          postfix = postfix + stack.pop();
        }
        stack.pop();
      } else {
        while (!stack.empty() && priority[stack.Top()] >= priority[c]) {
          if (!postfix.empty() && postfix.back() != ' ') {
            postfix = postfix + ' ';
          }
          postfix = postfix + stack.pop();
        }
        if (!postfix.empty() && postfix.back() != ' ') {
          postfix = postfix + ' ';
        }
        stack.push(c);
      }
    }
  }
  while (!stack.empty()) {
    if (!postfix.empty() && postfix.back() != ' ') {
      postfix = postfix + ' ';
    }
    postfix = postfix + stack.pop();
  }
  return postfix;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack;
  int n = 0;
  bool readingNum = false;
  for (char c : pref) {
    if (c == ' ') {
      if (readingNum) {
        stack.push(n);
        n = 0;
        readingNum = false;
      }
      continue;
    }
    if (isdigit(c)) {
      n = n * 10 + (c - '0');
      readingNum = true;
    } else {
      if (readingNum) {
        stack.push(n;
        n = 0;
        readingNum = false;
      }
      int x2 = stack.pop();
      int x1 = stack.pop();
      switch (c) {
      case '+': stack.push(x1 + x2); break;
      case '-': stack.push(x1 - x2); break;
      case '*': stack.push(x1 * x2); break;
      case '/': stack.push(x1 / x2); break;
      case '^': {
        int result = 1;
        for (int i = 0; i < x2; ++i) result = result * x1;
        stack.push(result);
        break;
      }
      }
    }
  }
  return stack.pop();
}
