// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  // добавьте код
  return std::string("");
}

int eval(const std::string& pref) {
  // добавьте код
  return 0;
}
// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string result;
  size_t i = 0;

  while (i < inf.length()) {
    if (std::isdigit(inf[i])) {
      while (i < inf.length() && std::isdigit(inf[i])) {
        result += inf[i++];
      }
      result += ' ';
      continue;
    } else if (inf[i] == '(') {
      stack.push('(');
    } else if (inf[i] == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        result += stack.pop();
        result += ' ';
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (isOperator(inf[i])) {
      while (!stack.isEmpty() && priority(stack.top()) >= priority(inf[i])) {
        result += stack.pop();
        result += ' ';
      }
      stack.push(inf[i]);
    }
    ++i;
  }

  while (!stack.isEmpty()) {
    result += stack.pop();
    result += ' ';
  }

  if (!result.empty() && result.back() == ' ')
    result.pop_back();

  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream iss(post);
  std::string token;

  while (iss >> token) {
    if (std::isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else if (token.length() == 1 && isOperator(token[0])) {
      int b = stack.pop();
      int a = stack.pop();
      int res = 0;
      switch (token[0]) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = a / b; break;
      }
      stack.push(res);
    }
  }

  return stack.pop();
}

