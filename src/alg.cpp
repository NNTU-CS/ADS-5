// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include "tstack.h"

void EndResult_CleanStack(TStack<char, 100>& stack, std::string& result) {
  while (!stack.IsEmpty()) {
    char symb = stack.Pop();
    if (symb == ')' || symb == '(') {
      throw std::runtime_error("extra paren");
    }
    result.push_back(symb);
    result.push_back(' ');
  }
  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string result;
  for (unsigned i = 0; i < inf.size(); ++i) {
    if (inf[i] >= '0' && inf[i] <= '9') {
      result.push_back(inf[i]);
      for (; i + 1 < inf.size() && inf[i + 1] >= '0' && inf[i + 1] <= '9'; ++i) {
        result.push_back(inf[i + 1]);
      }
      result.push_back(' ');
    } else if (inf[i] == '(') {
      stack.Push(inf[i]);
    } else if (inf[i] == '+' || inf[i] == '-') {
      while (!stack.IsEmpty() && stack.Top() != '(') {
        result += std::string(1, stack.Pop());
        result.push_back(' ');
      }
      stack.Push(inf[i]);
    } else if (inf[i] == '*' || inf[i] == '/') {
      while (!stack.IsEmpty() && (stack.Top() == '*' || stack.Top() == '/')) {
        result += std::string(1, stack.Pop());
        result.push_back(' ');
      }
      stack.Push(inf[i]);
    } else if (inf[i] == ')') {
      bool trueExpr = 0;
      while (stack.Size() > 0) {
        result += std::string(1, stack.Pop());
        result.push_back(' ');
        if (stack.Top() == '(') {
          stack.Pop();
          trueExpr = 1;
          break;
        }
      }
      if (!trueExpr) {
        throw std::runtime_error("Falsy expresion");
      }
    } else if (std::isspace(static_cast<unsigned char>(inf[i]))) {
      continue;
    } else {
      throw std::runtime_error("Falsy expresion");
    }
  }
  EndResult_CleanStack(stack, result);
  return result;
}

bool isSign(const unsigned char sign) {
  return sign == '+' || sign == '-' || sign == '*' || sign == '/';
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  for (unsigned i = 0; i < post.size(); ++i) {
    if (std::isdigit(static_cast<unsigned char>(post[i]))) {
      int digit = 0;
      for (; std::isdigit(static_cast<unsigned char>(post[i])); ++i) {
        digit += digit * 10 + post[i] - '0';
      }
      --i;
      stack.Push(digit);
    } else if (isSign(static_cast<unsigned char>(post[i]))) {
      if (stack.Size() < 2) {
        throw std::runtime_error("Not enough operator");
      }
      const int rhs = stack.Pop();
      const int lhs = stack.Pop();
      switch (post[i]) {
        case '+':
          stack.Push(lhs + rhs);
          break;
        case '-':
          stack.Push(lhs - rhs);
          break;
        case '*':
          stack.Push(lhs * rhs);
          break;
        case '/':
          if (rhs == 0) {
            throw std::runtime_error("division by zerro");
          }
          stack.Push(lhs / rhs);
          break;
      }
    } else if (std::isspace(static_cast<unsigned char>(post[i]))) {
      continue;
    } else {
      throw std::runtime_error("Неверное выражение");
    }
  }
  if (stack.Size() != 1) {
    throw std::runtime_error("Неверное выражение");
  }
  return stack.Pop();
}
