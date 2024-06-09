// Copyright 2021 NNTU-CS
#include <string>
#include <stack>
#include <algorithm>
#include "tstack.h"

bool isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int precedence(char ch) {
  if (ch == '*' || ch == '/')
    return 2;
  if (ch == '+' || ch == '-')
    return 1;
  return 0;
}

std::string infixToPostfix(std::string infix) {
  std::stack<char> operatorStack;
  std::string postfix;
  for (int i = 0; i < infix.length(); i++) {
    if (isOperator(infix[i])) {
      postfix.push_back(' ');
      while (!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(infix[i])) {
        postfix += operatorStack.top();
        operatorStack.pop();
        postfix.push_back(' ');
      }
      operatorStack.push(infix[i]);
    } else if (infix[i] == '(') {
      operatorStack.push(infix[i]);
    } else if (infix[i] == ')') {
      while (!operatorStack.empty() && operatorStack.top() != '(') {
        postfix.push_back(' ');
        postfix += operatorStack.top();
        operatorStack.pop();
      }
      operatorStack.pop();
    } else {
      postfix += infix[i];
    }
  }
  while (!operatorStack.empty()) {
    postfix.push_back(' ');
    postfix += operatorStack.top();
    operatorStack.pop();
  }
  return postfix;
}

std::string evaluate(char op, int operand1, int operand2) {
  switch (op) {
    case '+': return std::to_string(operand1 + operand2);
    case '-': return std::to_string(operand1 - operand2);
    case '*': return std::to_string(operand1 * operand2);
    case '/': return std::to_string(operand1 / operand2);
  }
  return "";
}

int evalPostfix(std::string postfix) {
  std::stack<std::string> operandStack;
  std::string spacer = " ";
  std::string op2;
  std::string op1;
  for (int i = 0; i < postfix.length(); i++) {
    if (isOperator(postfix[i])) {
      if (operandStack.top() == " ") {
        operandStack.pop();
      }
      if (operandStack.top() == "0") {
        while (!operandStack.empty() && operandStack.top() != spacer) {
          op2 += operandStack.top();
          operandStack.pop();
        }
        if (op2[0] == '0')
          std::reverse(op2.begin(), op2.end());
      } else {
        while (!operandStack.empty() && operandStack.top() != spacer) {
          op2 += operandStack.top();
          operandStack.pop();
          if (op2[0] == '0')
            std::reverse(op2.begin(), op2.end());
        }
        if (operandStack.top() == " ") {
          operandStack.pop();
          if (operandStack.top() == "0") {
            while (!operandStack.empty() && operandStack.top() != spacer) {
              op1 += operandStack.top();
              operandStack.pop();
            }
            if (op1[0] == '0')
              std::reverse(op1.begin(), op1.end());
          } else {
            while (!operandStack.empty() && operandStack.top() != spacer) {
              op1 += operandStack.top();
              operandStack.pop();
              if (op1[0] == '0')
                std::reverse(op1.begin(), op1.end());
            }
          }
        }
        std::string result = evaluate(postfix[i], std::stoi(op1), std::stoi(op2));
        operandStack.push(result);
      }
    } else {
      if (postfix[i] == ' ')
        operandStack.push(" ");
      else
        operandStack.push(std::to_string(postfix[i] - '0'));
    }
    op1 = " ";
    op2 = " ";
  }
  return std::stoi(operandStack.top());
}
