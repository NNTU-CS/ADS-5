// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}
std::string infx2pstfx(const std::string& inf) {
  std::string out;
  TStack<char, 100> stack;
  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        out += inf[i++];
      }
      out += ' ';
      --i;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        out += stack.pop();
        out += ' ';
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!stack.isEmpty() && priority(stack.get()) >= priority(c)) {
        out += stack.pop();
        out += ' ';
      }
      stack.push(c);
    }
  }
  while (!stack.isEmpty()) {
    out += stack.pop();
    out += ' ';
  }
  return out;
}
int eval(const std::string& pref) {
  TStack<int, 100> stack;
  int i = 0;
  while (i < pref.size()) {
    if (isdigit(pref[i])) {
      int num = 0;
      while (i < pref.size() && isdigit(pref[i])) {
        num = num * 10 + (pref[i++] - '0');
      }
      stack.push(num);
    } else if (pref[i] == '+' || pref[i] == '-' || pref[i] == '*' || pref[i] == '/') {
      int b = stack.pop();
      int a = stack.pop();
      int result = 0;
      if (pref[i] == '+') result = a + b;
      else if (pref[i] == '-') result = a - b;
      else if (pref[i] == '*') result = a * b;
      else if (pref[i] == '/') result = a / b;
      stack.push(result);
    }
    ++i;
  }
  return stack.pop();
}
