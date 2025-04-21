// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string output;
  std::map<char, int> priority = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0}
  };
  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        output += inf[i++];
      }
      output += ' ';
      --i;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (stack.top() != '(') {
        output += stack.pop();
        output += ' ';
      }
      stack.pop();
    } else if (priority.count(c)) {
      while (!stack.isEmpty() && priority[c] <= priority[stack.top()]) {
        output += stack.pop();
        output += ' ';
      }
      stack.push(c);
    }
  }
  while (!stack.isEmpty()) {
    output += stack.pop();
    output += ' ';
  }
  if (!output.empty() && output.back() == ' ') {
    output.pop_back();
  }
  return output;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream iss(post);
  std::string token;
  while (iss >> token) {
    if (isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else {
      int b = stack.pop();
      int a = stack.pop();
      switch (token[0]) {
        case '+': stack.push(a + b); break;
        case '-': stack.push(a - b); break;
        case '*': stack.push(a * b); break;
        case '/': stack.push(a / b); break;
      }
    }
  }
  return stack.pop();
}
