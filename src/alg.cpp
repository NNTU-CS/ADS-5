// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  std::map<char, int> priority = {
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2}
  };

  std::string result;
  TStack<char, 100> stack;
  for (size_t i = 0; i < inf.size(); ++i) {
    if (std::isdigit(inf[i])) {
      while (i < inf.size() && std::isdigit(inf[i])) {
        result += inf[i++];
      }
      result += ' ';
      --i;
    } else if (inf[i] == '(') {
      stack.push('(');
    } else if (inf[i] == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        result += stack.pop();
        result += ' ';
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (priority.count(inf[i])) {
      while (!stack.isEmpty() && priority[stack.top()] >= priority[inf[i]]) {
        result += stack.pop();
        result += ' ';
      }
      stack.push(inf[i]);
    }
  }

  while (!stack.isEmpty()) {
    result += stack.pop();
    result += ' ';
  }

  return result;
}

int eval(const std::string& post) {
  std::istringstream iss(post);
  std::string token;
  TStack<int, 100> stack;

  while (iss >> token) {
    if (std::isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else {
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
