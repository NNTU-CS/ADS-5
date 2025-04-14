// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include <sstream>
#include "tstack.h"

int precedence(char op) {
  switch (op) {
  case '+':
  case '-': return 1;
  case '*':
  case '/': return 2;
  default: return 0;
  }
}

std::string infx2pstfx(const std::string& inf) {
  std::string output;
  TStack<char, 100> opStack;
  for (size_t i = 0; i < inf.length(); i++) {
    char ch = inf[i];
    if (ch == ' ') {
        continue;
    }
    if (std::isdigit(ch)) {
      while (i < inf.length() && std::isdigit(inf[i])) {
        output.push_back(inf[i]);
          i++;
        }
        i--;
        output.push_back(' ');
    } else if (ch == '(') {
      opStack.push(ch);
    } else if (ch == ')') {
      while (!opStack.empty() && opStack.top() != '(') {
        output.push_back(opStack.top());
        output.push_back(' ');
        opStack.pop();
        }
        if (!opStack.empty() && opStack.top() == '(') {
          opStack.pop();
        } else {
          throw std::runtime_error("incorrect expression");
        }
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
        while (!opStack.empty()
          && precedence(opStack.top()) >= precedence(ch)) {
          output.push_back(opStack.top());
          output.push_back(' ');
          opStack.pop();
        }
        opStack.push(ch);
    } else {
      throw std::runtime_error(std::string("Invalid character") + ch);
    }
  }
  while (!opStack.empty()) {
    if (opStack.top() == '(' || opStack.top() == ')') {
      throw std::runtime_error("Incorrect expression");
    }
    output.push_back(opStack.top());
    output.push_back(' ');
    opStack.pop();
  }
  if (!output.empty() && output.back() == ' ') {
    output.pop_back();
  }
  return output;
}

int eval(const std::string& pref) {
  TStack<int, 100> numStack;
  std::istringstream iss(pref);
  std::string token;
  while (iss >> token) {
    if (std::isdigit(token[0])) {
      int num = std::stoi(token);
      numStack.push(num);
    } else if (token.length() == 1 && (token[0] == '+' || token[0] == '-'
        || token[0] == '*' || token[0] == '/')) {
      if (numStack.empty()) {
        throw std::runtime_error("Not enough operands for the operation");
      }
      int operand2 = numStack.top();
      numStack.pop();
      if (numStack.empty()) {
        throw std::runtime_error("Not enough operands for the operation");
      }
      int operand1 = numStack.top();
      numStack.pop();
      int result = 0;
      switch (token[0]) {
        case '+': result = operand1 + operand2; break;
        case '-': result = operand1 - operand2; break;
        case '*': result = operand1 * operand2; break;
        case '/':
          if (operand2 == 0) {
            throw std::runtime_error("Error");
          }
          result = operand1 / operand2;
          break;
        default:
          throw std::runtime_error("Error");
        }
        numStack.push(result);
    } else {
      throw std::runtime_error("Invalid token in the expression: ");
    }
  }
  if (numStack.empty()) {
    throw std::runtime_error("Stack is empty");
  }
  int finalResult = numStack.top();
  numStack.pop();
  if (!numStack.empty()) {
    throw std::runtime_error("Incorrect expression");
  }
  return finalResult;
}
