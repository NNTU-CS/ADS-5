// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::stringstream output;
  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        output << inf[i++];
      }
      output << ' ';
      i--;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.peek() != '(') {
        output << stack.pop() << ' ';
      }
      stack.pop();
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c)) {
        output << stack.pop() << ' ';
      }
      stack.push(c);
    }
  }
  while (!stack.isEmpty()) {
    output << stack.pop() << ' ';
  }
  std::string result = output.str();
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
