// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool operat(char oper) {
    return (oper == '+' || oper == '-' || oper == '(' ||
        oper == ')' || oper == '/' || oper == '*');
}
bool di(char v) {
    return (v >= '0' && v <= '9');
}

int prior(char oper) {
    if (oper == '-' || oper == '+')
        return 1;
    if (oper == '/' || oper == '*')
        return 2;
    return 0;
}
std::string infx2pstfx(std::string inf) {
  std::string novy;
  int f = 0;
  TStack <char, 100> stack1;
  for (char t : inf) {
    if (di(t)) {
      f++;
      if (f == 1) {
        novy += t;
        continue;
      }
      novy = novy + ' ' + t;
    } else if (operat(t)) {
      if (t == '(') {
        stack1.push(t);
      } else if (stack1.checkEmpty()) {
          stack1.push(t);
        } else if (prior(t) > prior(stack1.get())) {
          stack1.push(t);
        } else if (t == ')') {
          while (stack1.get() != '(') {
            novy = novy + ' ' + stack1.get();
            stack1.pop();
          }
          stack1.pop();
        } else {
          int u = prior(t);
          int o = prior(stack1.get());
          while (!stack1.checkEmpty() && u <= o) {
            novy = novy + ' ' + stack1.get();
            stack1.pop();
          }
          stack1.push(t);
        }
      }
    }
    while (!stack1.checkEmpty()) {
      novy = novy + ' ' + stack1.get();
      stack1.pop();
    }
  return novy;
}

int eval(std::string pref) {
  TStack <int, 100> stack2;
  for (char t : pref) {
    if (di(t)) {
      stack2.push(t - '0');
    } else if (operat(t)) {
      int u = stack2.get();
      stack2.pop();
      int o = stack2.get();
      stack2.pop();
      switch (t) {
        case '+':
          stack2.push(u + o);
          break;
        case '-':
          stack2.push(o - u);
          break;
        case '*':
          stack2.push(u * o);
          break;
        case '/':
          stack2.push(o / u);
          break;
        default:
          continue;
      }
    } else {
      continue;
    }
  }
  return stack2.get();
}
