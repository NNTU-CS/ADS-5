// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

bool is_math_operator(char c) {
  return (c == '+'  c == '-'  c == '*' || c == '/');
}

int operation_priority(char op) {
  switch (op) {
  case '+': case '-': return 1;
  case '*': case '/': return 2;
  default: return 0;
  }
}

std::string infx2pstfx(const std::string& inf) {
  // добавьте код
  return std::string("");
}

int eval(const std::string& pref) {
  // добавьте код
  return 0;
}
