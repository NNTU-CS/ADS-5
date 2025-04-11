// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>

template <typename DataType, int StackSize>
class TStack {
 private:
  DataType stackData[StackSize];
  int topOfStackIndex;

 public:
  TStack() : topOfStackIndex(-1) {
    for (int i = 0; i < StackSize; ++i) {
      stackData[i] = DataType();
    }
  }
  void push(const DataType& value) {
    if (topOfStackIndex < StackSize - 1) {
      stackData[++topOfStackIndex] = value;
    }
  }
  DataType pop() {
    if (topOfStackIndex >= 0) {
      return stackData[topOfStackIndex--];
    }
    return DataType();
  }
  DataType top() const {
    if (topOfStackIndex >= 0) {
      return stackData[topOfStackIndex];
    }
    return DataType();
  }
  bool isEmpty() const {
    return topOfStackIndex == -1;
  }
};

std::string infx2pstfx(const std::string& infixExpr) {
  TStack<char, 100> operatorStack;
  std::string postfixResult;
  std::map<char, int> operatorPrecedence = {
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2}
  };
  for (size_t i = 0; i < infixExpr.size(); ++i) {
    char currentChar = infixExpr[i];
    if (isdigit(currentChar)) {
      while (i < infixExpr.size() && isdigit(infixExpr[i])) {
        postfixResult += infixExpr[i++];
      }
      postfixResult += ' ';
      i--;
    } else if (currentChar == '(') {
      operatorStack.push(currentChar);
    } else if (currentChar == ')') {
      while (!operatorStack.isEmpty() && operatorStack.top() != '(') {
        postfixResult += operatorStack.pop();
        postfixResult += ' ';
      }
      operatorStack.pop();
    } else if (operatorPrecedence.count(currentChar)) {
      while (!operatorStack.isEmpty() && operatorStack.top() != '(' &&
             operatorPrecedence[operatorStack.top()] >=
                 operatorPrecedence[currentChar]) {
        postfixResult += operatorStack.pop();
        postfixResult += ' ';
      }
      operatorStack.push(currentChar);
    }
  }
  while (!operatorStack.isEmpty()) {
    postfixResult += operatorStack.pop();
    postfixResult += ' ';
  }
  if (!postfixResult.empty() && postfixResult.back() == ' ') {
    postfixResult.pop_back();
  }
  return postfixResult;
}

int eval(const std::string& postfixExpr) {
  TStack<int, 100> operandStack;
  std::string currentNumberString;
  for (char currentChar : postfixExpr) {
    if (isdigit(currentChar)) {
      currentNumberString += currentChar;
    } else if (currentChar == ' ' && !currentNumberString.empty()) {
      operandStack.push(std::stoi(currentNumberString));
      currentNumberString.clear();
    } else if (currentChar == '+' || currentChar == '-' ||
               currentChar == '*' || currentChar == '/') {
      int rightOperand = operandStack.pop();
      int leftOperand = operandStack.pop();
      switch (currentChar) {
        case '+': operandStack.push(leftOperand + rightOperand); break;
        case '-': operandStack.push(leftOperand - rightOperand); break;
        case '*': operandStack.push(leftOperand * rightOperand); break;
        case '/': operandStack.push(leftOperand / rightOperand); break;
      }
    }
  }
  return operandStack.pop();
}
