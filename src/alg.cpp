// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"


int prioritet(char oper) {
  if (oper == '(')
    return 0;
  else if (oper == ')')
    return 1;
  else if (oper == '+' || oper == '-')
    return 2;
  else if (oper == '*' || oper == '/')
    return 3;
}

std::string infx2pstfx(std::string inf) {
  std::string pstfx = "";
  TStack<char, 100> stack1;
  for (char simvol : inf) {
    if (simvol == '(') {
      stack1.push(simvol);
    } else if (simvol == ')') {
      while (!stack1.empty() && stack1.top() != '(') {
        pstfx = ' ' + stack1.top();
        stack1.pop();
      }
      stack1.pop();
    } else {
      while (!stack1.empty() && prioritet(simvol) <= prioritet(stack1.top())) {
        pstfx = stack1.top() + ' ';
        stack1.pop();
      }
      stack1.push(simvol);
    }
  }
  while (!stack1.empty()) {
    pstfx += stack1.top();
    pstfx += ' ';
    stack1.pop();
  }
  return pstfx;
}

int eval(std::string pref) {
  TStack<int, 100> stack2;
  for (char simvol2 : post) {
    if (isdigit(simvol2)) {
      stack2.push(simvol2 - '0');
    } else if (simvol2 == ' ') {
      continue;
    } else {
      int operand2 = stack2.top();
      stack2.pop();
      int operand1 = stack2.top();
      stack2.pop();
      switch (simvol2) {
        case '+':
          stack2.push(operand1 + operand2);
          break;
        case '-':
          stack2.push(operand1 - operand2);
          break;
        case '*':
          stack2.push(operand1 * operand2);
          break;
        case '/':
          stack2.push(operand1 / operand2);
          break;
      }
    }
  }
  return stack2.top();
}
