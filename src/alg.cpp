// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <stack>
#include "tstack.h"

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  std::string output;
  TStack<char, 100> stack1;
  std::istringstream iss(inf);
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0])) {
      output += token + " ";
    } else if (token[0] == '(') {
      stack1.push(token[0]);
    } else if (token[0] == ')') {
      while (!stack1.is_empty() && stack1.top() != '(') {
        output += stack1.pop() + " ";
      }
      stack1.pop();
    } else {
      while (!stack1.is_empty() && 
        precedence(stack1.top()) >= precedence(token[0])) {
          output += stack1.pop() + " ";
      }
      stack1.push(token[0]);
    }
  }

  while (!stack1.is_empty()) {
    output += stack1.pop() + " ";
  }

  return output;
}

int eval(const std::string& post) {
  TStack<int, 100> stack2;
  std::istringstream iss(post);
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0])) {
      stack2.push(std::stoi(token));
    } else {
      int b = stack2.pop();
      int a = stack2.pop();
      switch (token[0]) {
        case '+':
          stack2.push(a + b);
          break;
        case '-':
          stack2.push(a - b);
          break;
        case '*':
          stack2.push(a * b);
          break;
        case '/':
          stack2.push(a / b);
          break;
      }
    }
  }

  return stack2.pop();
}




