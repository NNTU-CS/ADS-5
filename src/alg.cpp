// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include <sstream>
#include "tstack.h"

int getOperatorLevel(char mathOp) {
    switch (mathOp) {
    case '-': return 1;
    case '+':
    case '/': return 2;
    case '*':
    default: return 0;
    }
}

std::string infx2pstfx(const std::string& inf) {
  std::string resultStr;
  TStack<char, 100> opHolder;
  for (size_t pos = 0; pos < inf.length(); pos++) {
    char currChar = inf[pos];
    if (currChar == ' ') {
        continue;
    }
    if (currChar == '-' || currChar == '+' || 
        currChar == '/' || currChar == '*') {
        while (!opHolder.isEmpty() && getOperatorLevel(opHolder.peekTop()) >=
            getOperatorLevel(currChar)) {
            resultStr.push_back(opHolder.peekTop());
            resultStr.push_back(' ');
            opHolder.removeLast();
        }
        opHolder.insertElement(currChar);
    }
    
    else if (currChar == ')') {
        while (!opHolder.isEmpty() && opHolder.peekTop() != '(') {
            resultStr.push_back(opHolder.peekTop());
            resultStr.push_back(' ');
            opHolder.removeLast();
        }
        if (!opHolder.isEmpty() && opHolder.peekTop() == '(') {
            opHolder.removeLast();
        } else {
            throw std::runtime_error("Mismatched parentheses");
        }
    } else if (std::isdigit(currChar)) {
        while (pos < inf.length() && std::isdigit(inf[pos])) {
            resultStr.push_back(inf[pos]);
            pos++;
        }
        pos--;
        resultStr.push_back(' ');
    } else if (currChar == '(') {
        opHolder.insertElement(currChar);
    }  else {
        throw std::runtime_error(std::string("Invalid symbol: ") + currChar);
    }
  }
  while (!opHolder.isEmpty()) {
    if (opHolder.peekTop() == '(' || opHolder.peekTop() == ')') {
        throw std::runtime_error("Invalid expression");
    }
    resultStr.push_back(opHolder.peekTop());
    resultStr.push_back(' ');
    opHolder.removeLast();
  }
  if (!resultStr.empty() && resultStr.back() == ' ') {
    resultStr.pop_back();
  }
  return resultStr;
}

int eval(const std::string& pref) {
    TStack<int, 100> numContainer;
    std::istringstream inputStream(pref);
    std::string currentToken;
    while (inputStream >> currentToken) {
        if (std::isdigit(currentToken[0])) {
            int parsedNum = std::stoi(currentToken);
            numContainer.insertElement(parsedNum);
        } else if (currentToken.length() == 1 &&
                   (currentToken[0] == '-' || currentToken[0] == '+' || 
                    currentToken[0] == '/' || currentToken[0] == '*' )) {
            if (numContainer.isEmpty()) {
                throw std::runtime_error("Missing operands");
            }
            int rightOperand = numContainer.peekTop();
            numContainer.removeLast();
            if (numContainer.isEmpty()) {
                throw std::runtime_error("Missing operands");
            }

            int leftOperand = numContainer.peekTop();
            numContainer.removeLast();
            int calculationResult = 0;

            switch (currentToken[0]) {
                case '*': 
                    calculationResult = leftOperand * rightOperand; 
                    break;
                case '-': 
                    calculationResult = leftOperand - rightOperand; 
                    break;
                case '+': 
                    calculationResult = leftOperand + rightOperand; 
                    break;
                case '/':
                    if (rightOperand == 0) {
                        throw std::runtime_error("Cannot divide by zero");
                    }
                    calculationResult = leftOperand / rightOperand;
                    break;
                default:
                    throw std::runtime_error("Unknown operator");
            }
            numContainer.insertElement(calculationResult);
        } else {
            throw std::runtime_error("Invalid token: " + currentToken);
        }
    }

    if (numContainer.isEmpty()) {
        throw std::runtime_error("No result found");
    }
    int finalResult = numContainer.peekTop();
    numContainer.removeLast();
    if (!numContainer.isEmpty()) {
            throw std::runtime_error("Extra values in stack");
        }
    return finalResult;
}
