// Copyright 2025 NNTU-CS
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

#include "tstack.h"

namespace {

int getPrecedence(char op) {
  switch (op) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    default:
      return 0;
  }
}

bool isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

}  // namespace

std::string infx2pstfx(const std::string& expr) {
  TStack<char, 128> opStack;
  std::string result;

  for (size_t i = 0; i < expr.length(); ++i) {
    char current = expr[i];

    if (std::isspace(static_cast<unsigned char>(current))) continue;

    if (std::isdigit(static_cast<unsigned char>(current))) {
      while (i < expr.length() && 
        std::isdigit(static_cast<unsigned char>(expr[i]))) {
        result += expr[i++];
      }
      result += ' ';
      --i;
    } else if (current == '(') {
      opStack.push(current);
    } else if (current == ')') {
      while (!opStack.isEmpty() && opStack.top() != '(') {
        result += opStack.top();
        result += ' ';
        opStack.pop();
      }
      if (!opStack.isEmpty()) opStack.pop();  // Remove '('
    } else if (isOperator(current)) {
      while (!opStack.isEmpty() && isOperator(opStack.top()) &&
             getPrecedence(opStack.top()) >= getPrecedence(current)) {
        result += opStack.top();
        result += ' ';
        opStack.pop();
      }
      opStack.push(current);
    }
  }

  while (!opStack.isEmpty()) {
    result += opStack.top();
    result += ' ';
    opStack.pop();
  }

  if (!result.empty() && result.back() == ' ') result.pop_back();
  return result;
}

int eval(const std::string& postfix) {
  std::stringstream stream(postfix);
  std::string part;
  TStack<int, 128> values;

  while (stream >> part) {
    if (part.length() == 1 && isOperator(part[0])) {
      if (values.size() < 2) {
        throw std::runtime_error("Invalid postfix expression");
      }
      int b = values.top(); values.pop();
      int a = values.top(); values.pop();

      switch (part[0]) {
        case '+':
          values.push(a + b);
          break;
        case '-':
          values.push(a - b);
          break;
        case '*':
          values.push(a * b);
          break;
        case '/':
          values.push(a / b);
          break;
      }
    } else {
      values.push(std::stoi(part));
    }
  }

  if (values.size() != 1) {
    throw std::runtime_error("Invalid postfix expression");
  }

  return values.top();
}
