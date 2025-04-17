// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

bool operacia(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int prioritet(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100>stack;
  std::string postfix;

  for (size_t i = 0; i < inf.length(); i++) {
    if (isspace(inf[i])) continue;

    if (isdigit(inf[i])) {
      postfix += inf[i];
      postfix += ' ';
    } else if (inf[i] == '(') {
      stack.push(inf[i]);
    } else if (inf[i] == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        postfix += stack.pop();
        postfix += ' ';
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (isOperator(inf[i])) {
      while (!stack.isEmpty() &&
       precedence(stack.top()) >= precedence(inf[i])) {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.push(inf[i]);
    }
  }

  while (!stack.isEmpty()) {
    postfix += stack.pop();
    postfix += ' ';
  }

  if (!postfix.empty() && postfix.back() == ' ')
    postfix.pop_back();

  return postfix;
}

int eval(const std::string& pref) {
  // добавьте код
  return 0;
}
