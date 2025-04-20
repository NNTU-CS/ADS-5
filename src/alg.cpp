// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <stdexcept>
#include <cctype>
#include "tstack.h"

int checkpriority(char sign) {
  switch (sign) {
  case '(': return 0;
  case ')': return 1;
  case '+': case '-': return 2;
  case '*': case '/': return 3;
  default: return -1;
  }
}

std::string infx2pstfx(const std::string& inf) {
  std::string postfix;
  TStack<char, 100> opStack;
  for (int i = 0; i < inf.length(); i++) {
    char temp = inf[i];
    if (isdigit(temp)) {
      std::string temp_string;
      while (i < inf.length() && isdigit(inf[i])) {
        temp_string += inf[++i];
        i++;
      }
      i--;
      postfix += temp_string;
      postfix += " ";
    } else if (temp == '(') {
      opStack.push(temp);
    } else if (temp == ')') {
      while (!opStack.isEmpty() && opStack.get() != '(') {
        postfix += opStack.get();
        postfix += " ";
        opStack.pop();
      }
      if (!opStack.isEmpty() && opStack.get() == '(') {
        opStack.pop();
      }
    } else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
      while (!opStack.isEmpty() && checkpriority(temp) <=
        checkpriority(opStack.get())) {
        postfix += opStack.get();
        postfix += " ";
        opStack.pop();
      }
      opStack.push(temp);
    } else if (temp == ' ') {
      continue;
    }
  }
  while (!opStack.isEmpty()) {
    postfix += opStack.get();
    postfix += " ";
    opStack.pop();
  }
  if (!postfix.empty() && postfix.back() == ' ') {
    postfix.pop_back();
  }
  return postfix;
}

int eval(const std::string& post) {
  TStack<int, 100> Stack;
  for (int i = 0; i < post.length(); ++i) {
    char ch = post[i];
    if (isspace(ch)) {
      continue;
    }
    if (isdigit(ch)) {
      int num = 0;
      while (i < post.length() && isdigit(post[i])) {
        num = num * 10 + (post[i] - '0');
        ++i;
      }
      --i;
      Stack.push(num);
    } else {
      if (Stack.isEmpty()) {
        throw std::runtime_error("Insufficient operands in postfix expression");
      }
      int b = Stack.pop();
      if (Stack.isEmpty()) {
        throw std::runtime_error("Insufficient operands in postfix expression");
      }
      int a = Stack.pop();

      switch (ch) {
      case '+': Stack.push(a + b); break;
      case '-': Stack.push(a - b); break;
      case '*': Stack.push(a * b); break;
      case '/':
        if (b == 0) {
          throw std::runtime_error("Division by zero");
        }
        Stack.push(a / b);
        break;
      default: throw std::invalid_argument("Invalid operator");
      }
    }
  }
  if (Stack.isEmpty()) {
    throw std::runtime_error("Empty stack after evaluation");
  }

  return Stack.pop();
}
