// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include "tstack.h"

int precedence(char op) {
  if (op == '*' || op == '/') return 2;
  if (op == '+' || op == '-') return 1;
  return 0;
}

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string out;

  for (size_t i = 0; i < inf.length(); ++i) {
    char ch = inf[i];

    if (std::isspace(ch)) continue;

    if (std::isdigit(ch)) {
      while (i < inf.length() && std::isdigit(inf[i])) {
        out += inf[i++];
      }
      out += ' ';
      --i;
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.isEmpty() && stack.peek() != '(') {
        out += stack.pop();
        out += ' ';
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (isOperator(ch)) {
      while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) {
        out += stack.pop();
        out += ' ';
      }
      stack.push(ch);
    }
  }

  while (!stack.isEmpty()) {
    out += stack.pop();
    out += ' ';
  }

  if (!out.empty() && out.back() == ' ')
    out.pop_back();

  return out;
}


int eval(const std::string& pref) {
  TStack<int, 100> stack;
  std::istringstream in(pref);
  std::string token;

  while (in >> token) {
    if (std::isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else if (isOperator(token[0]) && token.length() == 1) {
      int b = stack.pop();
      int a = stack.pop();
      if (token[0] == '+') stack.push(a + b);
      else if (token[0] == '-') stack.push(a - b);
      else if (token[0] == '*') stack.push(a * b);
      else if (token[0] == '/') stack.push(a / b);
    }
  }

  return stack.pop();
}

