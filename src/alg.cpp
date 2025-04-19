// Copyright 2021 NNTU-CS
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

#include "tstack.h"

int getPriority(char operation) {
  if (operation == '+' || operation == '-') return 1;
  if (operation == '*' || operation == '/') return 2;
  return 0;
}

bool isOperator(char symbol) {
  return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/');
}

std::string infx2pstfx(const std::string& infix) {
  std::string postfix;
  TStack<char, 128> operatorStack;

  for (size_t i = 0; i < infix.length(); ++i) {
    char currentChar = infix[i];

    if (std::isspace(static_cast<unsigned char>(currentChar))) continue;

    if (std::isdigit(static_cast<unsigned char>(currentChar))) {
      while (i < infix.length() &&
             std::isdigit(static_cast<unsigned char>(infix[i]))) {
        postfix += infix[i];
        ++i;
      }
      postfix += ' ';
      --i;
    } else if (currentChar == '(') {
      operatorStack.push(currentChar);
    } else if (currentChar == ')') {
      while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
        postfix += operatorStack.peek();
        postfix += ' ';
        operatorStack.pop();
      }
      if (!operatorStack.isEmpty()) operatorStack.pop();
    } else if (isOperator(currentChar)) {
      while (!operatorStack.isEmpty() && isOperator(operatorStack.peek()) &&
             getPriority(operatorStack.peek()) >= getPriority(currentChar)) {
        postfix += operatorStack.peek();
        postfix += ' ';
        operatorStack.pop();
      }
      operatorStack.push(currentChar);
    }
  }

  while (!operatorStack.isEmpty()) {
    postfix += operatorStack.peek();
    postfix += ' ';
    operatorStack.pop();
  }

  if (!postfix.empty() && postfix.back() == ' ') postfix.pop_back();
  return postfix;
}

int eval(const std::string& postfix) {
  std::stringstream stream(postfix);
  std::string token;
  TStack<int, 128> valueStack;

  while (stream >> token) {
    if (token.length() == 1 && isOperator(token[0])) {
      if (valueStack.size() < 2)
        throw std::runtime_error("Invalid postfix expression");
      int rightOperand = valueStack.peek();
      valueStack.pop();
      int leftOperand = valueStack.peek();
      valueStack.pop();
      int result;

      switch (token[0]) {
        case '+':
          result = leftOperand + rightOperand;
          break;
        case '-':
          result = leftOperand - rightOperand;
          break;
        case '*':
          result = leftOperand * rightOperand;
          break;
        case '/':
          result = leftOperand / rightOperand;
          break;
      }
      valueStack.push(result);
    } else {
      valueStack.push(std::stoi(token));
    }
  }

  if (valueStack.size() != 1)
    throw std::runtime_error("Invalid postfix expression");
  return valueStack.peek();
}
