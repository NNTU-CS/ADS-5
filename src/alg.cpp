// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

TStack<char, 100> stack1;
TStack<int, 100> stack2;

int Priority(char operand) {
  if (operand == '+' || operand == '-') return 1;
  if (operand == '*' || operand == '/') return 2;
  return 0;
}
std::string infx2pstfx(std::string inf) {
  std::string postfix;
  TStack<char, 100> stack;
  for (char c : inf) {
    if (isdigit(c)) {
      postfix = postfix + c + ' ';
    } else if (c == '(') {
      stack.add(c);
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!stack.isEmpty() && Priority(stack.show()) >= Priority(c)) {
        postfix = postfix + stack.show() + ' ';
        stack.pop();
      }
      stack.add(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.show() != '(') {
        postfix = postfix + stack.show() + ' ';
        stack.pop();
      }
      stack.pop();
    }
  }
  while (!stack.isEmpty()) {
    postfix = postfix + stack.show() + ' ';
    stack.pop();
  }
  if (!postfix.empty()) {
    postfix.pop_back();
  }
  return postfix;
}

int eval(std::string pref) {
  std::string strNumber = "";
  for (char c : pref) {
    if (c != ' ' && c != '+' && c != '-' && c != '*' && c != '/') {
      strNumber += c;
    }
    if (c == ' ') {
      if (!strNumber.empty()) {
        int num = std::stoi(strNumber);
        stack2.add(num);
        strNumber = "";
      }
    }
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      int b = stack2.show();
      stack2.pop();
      int a = stack2.show();
      stack2.pop();

      if (c == '+') {
        stack2.add((a + b));
      } else if (c == '-') {
        stack2.add((a - b));
      } else if (c == '*') {
        stack2.add((a * b));
      } else if (c == '/') {
        stack2.add((a / b));
      }
    }
  }

  return stack2.show();
}
