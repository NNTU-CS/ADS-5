// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isDigit(char b) {
  return (b >= '0' && b <= '9');
}
bool isOperator(char z) {
  return (z == '+' ||  z == '-' || z == '*' ||
  z == '/' ||  z == '(' || z == ')');
}
int Prioritet(char v) {
  if (v == '+' || v == '-')
  return 1;
  if (v == '*' || v == '/')
  return 2;
return 0;
}
std::string infx2pstfx(std::string inf) {
  std::string pos;
  int count = 0;
    TStack <char, 100> stack;
    for (char c : inf) {
      if (isDigit(c)) {
        count++;
      if (count == 1) {
        pos += c;
          continue;
            }
            pos = pos + ' ' + c;
      } else if (isOperator(c)) {
        if (c == '(') {
          stack.push(c);
      } else if (stack.isEmpty()) {
          stack.push(c);
      } else if (Prioritet(c) > Prioritet(stack.get())) {
          stack.push(c);
      } else if (c == ')') {
        while (stack.get() != '(') {
          pos = pos + ' ' + stack.get();
            stack.pop();
        }
        stack.pop();
      } else {
        int a = Prioritet(c);
        int b = Prioritet(stack.get());
          while (!stack.isEmpty() && a <= b) {
            pos = pos + ' ' + stack.get();
              stack.pop();
          }
          stack.push(c);
      }
    }
  }
  while (!stack.isEmpty()) {
    pos = pos + ' ' + stack.get();
      stack.pop();
  }
return pos;
}


int eval(std::string pref) {
  TStack <int, 100> stack;
  for (char c : pref) {
    if (isDigit(c)) {
      stack.push(c - '0');
    } else if (isOperator(c)) {
      int q = stack.get();
      stack.pop();
      int w = stack.get();
      stack.pop();
      switch (c) {
        case '+':
          stack.push(q + w);
          break;
        case '-':
          stack.push(w - q);
          break;
        case '*':
          stack.push(q * w);
          break;
        case '/':
          stack.push(w / q);
          break;
        default:
          continue;
      }
    } else {
      continue;
    }
  }
return stack.get();
}
