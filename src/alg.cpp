// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "tstack.h"

int GetOperatorPriority(char operation) {
  switch (operation) {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default: return 0;
  }
}

std::string ConvertInfixToPostfix(const std::string& infixExpr) {
  std::string postfixResult;
  TStack<char, 100> operatorStack;
    
  for (size_t currentPos = 0; currentPos < infixExpr.length(); currentPos++) {
    char currentChar = infixExpr[currentPos];
    if (currentChar == ' ') {
      continue;
    }
    if (std::isdigit(currentChar)) {
      while (currentPos < infixExpr.length() && std::isdigit(infixExpr[currentPos])) {
        postfixResult.push_back(infixExpr[currentPos]);
        currentPos++;
      }
      currentPos--;
      postfixResult.push_back(' ');
    } 
    else if (currentChar == '(') {
      operatorStack.push(currentChar);
    } 
    else if (currentChar == ')') {
      while (!operatorStack.empty() && operatorStack.top() != '(') {
        postfixResult.push_back(operatorStack.top());
        postfixResult.push_back(' ');
        operatorStack.pop();
      }
      if (!operatorStack.empty() && operatorStack.top() == '(') {
        operatorStack.pop();
      } else {
        throw std::runtime_error("incorrect expression");
      }
    }
    else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
      while (!operatorStack.empty()
        && GetOperatorPriority(operatorStack.top()) >= GetOperatorPriority(currentChar)) {
        postfixResult.push_back(operatorStack.top());
        postfixResult.push_back(' ');
        operatorStack.pop();
      }
      operatorStack.push(currentChar);
    } else {
      throw std::runtime_error(std::string("Invalid character") + currentChar);
    }
  }
  while (!operatorStack.empty()) {
    if (operatorStack.top() == '(' || operatorStack.top() == ')') {
      throw std::runtime_error("Incorrect expression");
    }
    postfixResult.push_back(operatorStack.top());
    postfixResult.push_back(' ');
    operatorStack.pop();
  }
  if (!postfixResult.empty() && postfixResult.back() == ' ') {
    postfixResult.pop_back();
  }
  return postfixResult;
}

int EvaluatePostfix(const std::string& postfixExpr) {
  TStack<int, 100> operandStack;
  std::istringstream exprStream(postfixExpr);
  std::string currentToken;
  while (exprStream >> currentToken) {
    if (std::isdigit(currentToken[0])) {
      int number = std::stoi(currentToken);
      operandStack.push(number);
    } 
    else if (currentToken.length() == 1 && (currentToken[0] == '+' || currentToken[0] == '-'
      || currentToken[0] == '*' || currentToken[0] == '/')) {
      if (operandStack.empty()) {
        throw std::runtime_error("not enough operands for the operation");
      }
      int rightOperand = operandStack.top();
      operandStack.pop();
      if (operandStack.empty()) {
        throw std::runtime_error("not enough operands for the operation");
      }
      int leftOperand = operandStack.top();
      operandStack.pop();
      int operationResult = 0;
      switch (currentToken[0]) {
        case '+': operationResult = leftOperand + rightOperand; break;
        case '-': operationResult = leftOperand - rightOperand; break;
        case '*': operationResult = leftOperand * rightOperand; break;
        case '/':
          if (rightOperand == 0) {
            throw std::runtime_error("error");
          }
          operationResult = leftOperand / rightOperand;
          break;
        default:
        throw std::runtime_error("error");
      }
      operandStack.push(operationResult);
    } else {
      throw std::runtime_error("Invalid token in the expression: ");
    }
  }
  if (operandStack.empty()) {
    throw std::runtime_error("Stack is empty");
  }
  int finalResult = operandStack.top();
  operandStack.pop();
  if (!operandStack.empty()) {
    throw std::runtime_error("Incorrect expression");
  }
  return finalResult;
}
