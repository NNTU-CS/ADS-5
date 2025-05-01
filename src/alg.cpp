// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

static int priority(char sign) {
  if (sign == '+' || sign == '-') return 1;
  if (sign == '*' || sign == '/') return 2;
  if (sign == '(') return 0;
}
char isOp(char sign) {
  return sign == '+' || sign == '-' || sign == '*' || sign == '/';
}
std::string infx2pstfx(const std::string& inf) {
  TStack <char, 100> stack1;
  std::string result;
  for (int i = 0; i < inf.size(); i++) {
    char c = inf[i];
    if (c == ' ') continue;
    if (isDigit(c)) {
      result += c;
      result += ' ';
    }
    if (c == '(') stack1.push(c);
    if (c == ')') {
      result += ' ';
      while (!stack1.isEmpty() && stack1.getTop() != '(') {
        result += stack1.pop();
      }
      stack1.pop();
      result += ' ';
    }
    if (isOp(c)) {
      while (!stack1.isEmpty() && priority(stack1.getTop()) >= priority(c)) {
        result += stack1.pop();
      }
      stack1.push(c);
      result += ' ';
    }
  }
  while (!stack1.isEmpty()) {
    result += ' ';
    result += stack1.pop();
  }
  return result;
}
int eval(const std::string& post) {
  TStack <int, 100> stack2;
  std::string currentNumber;
  for (size_t i = 0; i < post.size(); ++i) {
    char c = post[i];
    if (isspace(c)) {
      continue;
    }
    if (isdigit(c) || c == '.') {
      currentNumber += c;
      if (i + 1 < post.size() && (isDigit(post[i + 1]) || post[i + 1] == '.')) {
        continue;
      }
      stack2.push(stoi(currentNumber));
      currentNumber.clear();
      continue;
    }
    if (isOp(c)) {
      double b = stack2.getTop(); stack2.pop();
      double a = stack2.getTop(); stack2.pop();
      switch (c) {
      case '+': stack2.push(a + b); break;
      case '-': stack2.push(a - b); break;
      case '*': stack2.push(a * b); break;
      case '/':
        if (b == 0) throw std::runtime_error("Деление на ноль");
        stack2.push(a / b);
        break;
        continue;
      }
    }
  }
  return stack2.getTop();
}
