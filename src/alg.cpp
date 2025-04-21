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
  return (c >= '0') && (c <= '9');
}
bool isOperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string postfix;
  bool needSpace = false;
  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    if (c == ' ') continue;
    if (isDigit(c)) {
      if (needSpace) postfix += ' ';
      postfix += c;
      while (i + 1 < inf.size() && isDigit(inf[i+1])) {
        postfix += inf[++i];
      }
      needSpace = true;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        if (needSpace) postfix += ' ';
        postfix += stack.pop();
        needSpace = true;
      }
      stack.pop();
    } else if (isOperator(c)) {
      while (!stack.isEmpty() && op_priority[stack.top()] >= op_priority[c]) {
        if (needSpace) postfix += ' ';
        postfix += stack.pop();
        needSpace = true;
      }
      stack.push(c);
    }
  }
  while (!stack.isEmpty()) {
    if (needSpace) postfix += ' ';
    postfix += stack.pop();
    needSpace = true;
  }
  return postfix;
}
int eval(const std::string& pref) {
  TStack<int, 100> stack;
  std::string currentNum;
  for (char c : pref) {
    if (c == ' ') {
      if (!currentNum.empty()) {
        stack.push(std::stoi(currentNum));
        currentNum.clear();
      }
      continue;
    }
    if (isDigit(c)) {
      currentNum += c;
    } else {
      if (!currentNum.empty()) {
        stack.push(std::stoi(currentNum));
        currentNum.clear();
      }
      int right = stack.pop();
      int left = stack.pop();
      switch (c) {
        case '+': stack.push(left + right); break;
        case '-': stack.push(left - right); break;
        case '*': stack.push(left * right); break;
        case '/': stack.push(left / right); break;
        case '^': {
          int res = 1;
          for (int i = 0; i < right; ++i) res *= left;
          stack.push(res);
          break;
        }
      }
    }
  }
  return stack.pop();
}
