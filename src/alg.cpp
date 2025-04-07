// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include "tstack.h"

int GetPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  std::string result;
  TStack<char, 100> stack;

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    if (c == ' ') continue;

    if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        result += inf[i++];
      }
      i--;
      result += ' ';
    } else if (c == '(') {
      stack.Push(c);
    } else if (c == ')') {
      while (!stack.IsEmpty() && stack.Top() != '(') {
        result += stack.Top();
        result += ' ';
        stack.Pop();
      }
      stack.Pop();
    } else {
      while (!stack.IsEmpty() && 
             GetPriority(stack.Top()) >= GetPriority(c)) {
        result += stack.Top();
        result += ' ';
        stack.Pop();
      }
      stack.Push(c);
    }
  }

  while (!stack.IsEmpty()) {
    result += stack.Top();
    result += ' ';
    stack.Pop();
  }

  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }

  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream iss(post);
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0])) {
      stack.Push(std::stoi(token));
    } else {
      int rhs = stack.Top(); stack.Pop();
      int lhs = stack.Top(); stack.Pop();

      if (token == "+") stack.Push(lhs + rhs);
      else if (token == "-") stack.Push(lhs - rhs);
      else if (token == "*") stack.Push(lhs * rhs);
      else if (token == "/") stack.Push(lhs / rhs);
    }
  }

  return stack.Top();
}
