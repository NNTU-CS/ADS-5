// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  std::map<char, int> priority;
  priority['+'] = 1;
  priority['-'] = 1;
  priority['*'] = 2;
  priority['/'] = 2;
  priority['^'] = 3;
  std::string postExp = "";
  TStack<char> opStack;
  for (char c : inf) {
    if (isalnum(c)) {
      postExp += c;
    }
    else if (c == '(') {
      opStack.push(c);
    }
    else if (c == ')') {
      while (!opStack.isEmpty() && opStack.top() != '(') {
        postExp += opStack.top();
        opStack.pop();
      }
      opStack.pop();
    } else {
      while (!opStack.isEmpty() && opStack.top() != '(' &&
          priority[opStack.top()] >= priority[c]) {
        postExp += opStack.top();
        opStack.pop();
      }
      opStack.push(c);
    }
  }
  while (!opStack.isEmpty()) {
    postExp += opStack.top();
    opStack.pop();
  }
  return postExp;
}
int eval(std::string post) {
  TStack<int> numStack;
  for (char c : post) {
    if (isdigit(c)) {
      numStack.push(c - '0');
    } else {
      int num2 = numStack.top();
      numStack.pop();
      int num1 = numStack.top();
      numStack.pop();
      switch (c) {
      case '+':
        numStack.push(num1 + num2);
        break;
      case '-':
        numStack.push(num1 - num2);
        break;
      case '*':
        numStack.push(num1 * num2);
        break;
      case '/':
        numStack.push(num1 / num2);
        break;
      case '^':
        numStack.push(pow(num1, num2));
        break;
      }
    }
  }
  return numStack.top();
