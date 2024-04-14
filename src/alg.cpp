// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char a) {
  if (a == '+' || a == '-')
    return 1;
  if (a == '*' || a == '/')
    return 2;
  return 0;
}

bool isZnak(char a) {
  return (a == '+' || a == '-' || a == '*' || a == '/');
}

std::string infx2pstfx(std::string inf) {
  std::string inf2;
  TStack<char, 100> stack1;
  for (char i : inf) {
    if (i >= '0' && i <= '9') {
      inf2 = inf2 + i + ' ';
    } else if (i == '(') {
      stack1.push(i);
    } else if (isZnak(i)) {
      while (!stack1.isEmpty() && prioritet(stack1.get()) >= prioritet(i)) {
        inf2 = inf2 + stack1.get() + ' ';
        stack1.pop();
      }
      stack1.push(i);
    } else if (i == ')') {
      while (!stack1.isEmpty() && stack1.get() != '(') {
        inf2 = inf2 + stack1.get() + ' ';
        stack1.pop();
      }
      stack1.pop();
    }
  }
  while (!stack1.isEmpty()) {
    inf2 = inf2 + stack1.get() + ' ';
    stack1.pop();
  }
  if (!inf2.empty()) {
    inf2.pop_back();
  }
  return inf2;
}

int eval(std::string pref) {
  TStack<int, 100> stack2;
  for (char i : pref) {
    if (i >= '0' && i <= '9') {
      stack2.push(i - '0');
    } else if (isZnak(i)) {
      int x = stack2.get();
      stack2.pop();
      int y = stack2.get();
      stack2.pop();
      switch (i) {
        case '+':
          stack2.push(y + x);
          break;
        case '-':
          stack2.push(y - x);
          break;
        case '*':
          stack2.push(y * x);
          break;
        case '/':
          stack2.push(y / x);
          break;
        default:
          continue;
      }
    }
  }
  return stack2.get();
}
