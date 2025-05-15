// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include "tstack.h"

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack1;
  std::string output;
  std::istringstream iss(inf);
  std::string token;

  while (iss >> token) {
    if (std::isdigit(token[0])) {
      output += token + " ";
    } else if (token[0] == '(') {
      stack1.push('(');
    } else if (token[0] == ')') {
      while (!stack1.isEmpty() && stack1.peek() != '(') {
        output += stack1.pop();
        output += " ";
      }
      stack1.pop();
    } else {
      while (!stack1.isEmpty() &&
             precedence(stack1.peek()) >= precedence(token[0])) {
        output += stack1.pop();
        output += " ";
      }
      stack1.push(token[0]);
    }
  }

  while (!stack1.isEmpty()) {
    output += stack1.pop();
    output += " ";
  }

  return output;
}

int eval(const std::string& post) {
  TStack<int, 100> stack2;
  std::istringstream iss(post);
  std::string token;

  while (iss >> token) {
    if (std::isdigit(token[0])) {
      stack2.push(std::stoi(token));
    } else {
      int right = stack2.pop();
      int left = stack2.pop();
      switch (token[0]) {
        case '+': stack2.push(left + right); break;
        case '-': stack2.push(left - right); break;
        case '*': stack2.push(left * right); break;
        case '/':
          if (right == 0) {
            throw std::runtime_error("Division by zero");
          }
          stack2.push(left / right);
          break;
      }
    }
  }

  return stack2.pop();
}
