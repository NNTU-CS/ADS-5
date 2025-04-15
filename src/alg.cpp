// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "tstack.h"

int getPriority(char op) {
  switch (op) {
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    default: return 0;
  }
}

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infixToPostfix(const std::string& infixExpr) {
  TStack<char, 100> opStack;
  std::ostringstream output;
  bool isDigitPrevious = false;

  for (char ch : infixExpr) {
    if (ch == ' ') continue;

    if (isdigit(ch)) {
      if (isDigitPrevious) {
        output << ch;
      } else {
        if (!output.str().empty()) output << ' ';
        output << ch;
      }
      isDigitPrevious = true;
    } else {
      isDigitPrevious = false;
      
      if (ch == '(') {
        opStack.push(ch);
      } else if (ch == ')') {
        while (!opStack.isEmpty() && opStack.peek() != '(') {
          output << ' ' << opStack.pop();
        }
        if (!opStack.isEmpty()) opStack.pop();
      } else if (isOperator(ch)) {
        while (!opStack.isEmpty() && opStack.peek() != '(' &&
            getPriority(ch) <= getPriority(opStack.peek())) {
          output << ' ' << opStack.pop();
        }
        opStack.push(ch);
      }
    }
  }

  while (!opStack.isEmpty()) {
    output << ' ' << opStack.pop();
  }
  
  std::string result = output.str();
  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
  return result;
}

int evaluatePostfix(const std::string& postfixExpr) {
  TStack<int, 100> evalStack;
  std::istringstream iss(postfixExpr);
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0])) {
      evalStack.push(std::stoi(token));
    } else if (isOperator(token[0]) && token.size() == 1) {
      if (evalStack.isEmpty()) throw std::invalid_argument("Not enough operands");
      int rightOperand = evalStack.pop();
      
      if (evalStack.isEmpty()) throw std::invalid_argument("Not enough operands");
      int leftOperand = evalStack.pop();

      switch (token[0]) {
        case '+': evalStack.push(leftOperand + rightOperand); break;
        case '-': evalStack.push(leftOperand - rightOperand); break;
        case '*': evalStack.push(leftOperand * rightOperand); break;
        case '/':
          if (rightOperand == 0) throw std::runtime_error("Division by zero");
          evalStack.push(leftOperand / rightOperand);
          break;
      }
    }
  }

  if (evalStack.isEmpty()) throw std::invalid_argument("Empty expression");
  int result = evalStack.pop();
  if (!evalStack.isEmpty()) throw std::invalid_argument("Too many operands");
  return result;
}
