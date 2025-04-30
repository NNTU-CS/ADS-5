// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool is_number_symbol(char sym) {
  return sym >= '0' && sym <= '9';
}

bool is_math_symbol(char sym) {
  return (sym == '+' || sym == '-' || sym == '*' || sym == '/');
}

int get_priority(char op) {
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
