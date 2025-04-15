// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "tstack.h"

int prior(const char op) {
  switch (op) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    default:  return -1;
  }
}

std::string infx2pstfx(const std::string& infix) {
  std::string postfixStr;
  TStack<char, 100> operatorStack;
  bool addSpace = false;
  for (size_t index = 0; index < infix.size(); index++) {
    char currentChar = infix[index];
    int currentPriority = prior(currentChar);
    if (currentPriority == -1) {
      if (addSpace) postfixStr += ' ';
      postfixStr += currentChar;
      addSpace = false;
    } else if (currentChar == '(') {
      operatorStack.push(currentChar);
      addSpace = false;
    } else if (currentChar == ')') {
      while (!operatorStack.empty() && operatorStack.top() != '(') {
        postfixStr += ' ';
        postfixStr += operatorStack.top();
        operatorStack.pop();
      }
      operatorStack.pop();
      addSpace = true;
    } else {
      while (!operatorStack.empty() &&
             prior(operatorStack.top()) >= currentPriority &&
             operatorStack.top() != '(') {
        postfixStr += ' ';
        postfixStr += operatorStack.top();
        operatorStack.pop();
      }
      postfixStr += ' ';
      operatorStack.push(currentChar);
      addSpace = false;
    }
  }
  while (!operatorStack.empty()) {
    postfixStr += ' ';
    postfixStr += operatorStack.top();
    operatorStack.pop();
  }
  return postfixStr;
}
int eval(const std::string& postfix) {
  TStack<int, 100> calculationStack;
  std::string currentNumber;
  for (size_t index = 0; index < postfix.length(); index++) {
    char currentChar = postfix[index];
    if (isdigit(currentChar)) {
      currentNumber += currentChar;
    } else if (currentChar == ' ') {
      if (!currentNumber.empty()) {
        calculationStack.push(std::stoi(currentNumber));
        currentNumber.clear();
      }
    } else if (prior(currentChar) >= 2) {
      if (calculationStack.empty()) continue;
      int rightOperand = calculationStack.top();
      calculationStack.pop();
      if (calculationStack.empty()) continue;
      int leftOperand = calculationStack.top();
      calculationStack.pop();
      switch (currentChar) {
        case '+': calculationStack.push(leftOperand + rightOperand); break;
        case '-': calculationStack.push(leftOperand - rightOperand); break;
        case '*': calculationStack.push(leftOperand * rightOperand); break;
        case '/': calculationStack.push(leftOperand / rightOperand); break;
      }
    }
  }
  if (!currentNumber.empty()) {
    calculationStack.push(std::stoi(currentNumber));
  }
  return calculationStack.empty() ? 0 : calculationStack.top();
}
