// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getOpPriority(char operationSign) {
  std::pair<char, int> priorityTable[6];
  switch (operationSign) {
    case '(': priorityTable[0] = {'(', 0}; break;
    case ')': priorityTable[1] = {')', 1}; break;
    case '+': priorityTable[2] = {'+', 2}; break;
    case '-': priorityTable[3] = {'-', 2}; break;
    case '*': priorityTable[4] = {'*', 3}; break;
    case '/': priorityTable[5] = {'/', 3}; break;
  }
  int foundPriority = -1;
  for (int tableIdx = 0; tableIdx < 6; ++tableIdx) {
    if (operationSign == priorityTable[tableIdx].first) {
      foundPriority = priorityTable[tableIdx].second;
      break;
    }
  }
  return foundPriority;
}

std::string formatExpression(const std::string& inputExpr) {
  if (inputExpr.length() <= 2) return inputExpr;
  int startPos = 2 - inputExpr.length() % 2;
  std::string resultStr(inputExpr, 0, startPos);
  for (auto symbol = inputExpr.begin() + startPos; 
       symbol != inputExpr.end();) {
    resultStr += ' ';
    resultStr += *symbol++;
  }
  return resultStr;
}

std::string infx2pstfx(std::string inputExpr) {
  std::string outputResult;
  TStack<char, 100> operationsStack;
  
  for (auto& currentChar : inputExpr) {
    int charPriority = getOpPriority(currentChar);
    if (charPriority == -1) {
      outputResult += currentChar;
    } else {
      if (operationsStack.get() < charPriority || 
          charPriority == 0 || 
          operationsStack.isEmpty()) {
        operationsStack.push(currentChar);
      } else if (currentChar == ')') {
        char stackTop = operationsStack.get();
        while (getOpPriority(stackTop) >= charPriority) {
          outputResult += stackTop;
          operationsStack.pop();
          stackTop = operationsStack.get();
        }
        operationsStack.pop();
      } else {
        char stackTop = operationsStack.get();
        while (getOpPriority(stackTop) >= charPriority) {
          outputResult += stackTop;
          operationsStack.pop();
          stackTop = operationsStack.get();
        }
        operationsStack.push(currentChar);
      }
    }
  }
  
  while (!operationsStack.isEmpty()) {
    outputResult += operationsStack.get();
    operationsStack.pop();
  }
  
  return formatExpression(outputResult);
}

int performCalculation(const int& firstOperand,
                      const int& secondOperand,
                      const int& operationType) {
  switch (operationType) {
    case '+': return firstOperand + secondOperand;
    case '-': return firstOperand - secondOperand;
    case '*': return firstOperand * secondOperand;
    case '/': return firstOperand / secondOperand;
    default: return 0;
  }
}

int eval(std::string postfixExpr) {
  TStack<int, 100> calculationStack;
  std::string currentNumber = "";
  
  for (size_t charPos = 0; charPos < postfixExpr.size(); charPos++) {
    if (getOpPriority(postfixExpr[charPos]) == -1) {
      if (postfixExpr[charPos] == ' ') {
        continue;
      } else if (isdigit(postfixExpr[charPos + 1])) {
        currentNumber += postfixExpr[charPos];
        continue;
      } else {
        currentNumber += postfixExpr[charPos];
        calculationStack.push(atoi(currentNumber.c_str()));
        currentNumber = "";
      }
    } else {
      int rightOp = calculationStack.get();
      calculationStack.pop();
      int leftOp = calculationStack.get();
      calculationStack.pop();
      calculationStack.push(performCalculation(leftOp,
                                             rightOp,
                                             postfixExpr[charPos]));
    }
  }
  return calculationStack.get();
}
