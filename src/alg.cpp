// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
bool opera(char oper) {
    return (oper == '+' || oper == '-' || oper == '(' ||
      oper == ')' || oper == '/' || oper == '*');
}
bool div(char v) {
    return (v >= '0' && v <= '9');
}

int priority(char oper) {
    if (oper == '-' || oper == '+')
        return 1;
    if (oper == '/' || oper == '*')
        return 2;
    return 0;
}
std::string infx2pstfx(std::string inf) {
  std::string now;
  int f = 0;
  TStack <char, 100> stack_1;
  for (char t : inf) {
    if (div(t)) {
      f++;
      if (f == 1) {
        now += t;
        continue;
      }
      now = now + ' ' + t;
    } else if (opera(t)) {
      if (t == '(') {
        stack_1.push(t);
      } else if (stack_1.checkEmpty()) {
          stack_1.push(t);
        } else if (priority(t) > priority(stack_1.get())) {
          stack_1.push(t);
        } else if (t == ')') {
          while (stack_1.get() != '(') {
            now = now + ' ' + stack_1.get();
            stack_1.pop();
          }
          stack_1.pop();
        } else {
          int u = priority(t);
          int o = priority(stack_1.get());
          while (!stack_1.checkEmpty() && u <= o) {
            now = now + ' ' + stack_1.get();
            stack_1.pop();
          }
          stack_1.push(t);
        }
      }
    }
    while (!stack_1.checkEmpty()) {
      now = now + ' ' + stack_1.get();
      stack_1.pop();
    }
  return now;
}

int eval(std::string pref) {
  TStack <int, 100> stack_2;
  for (char t : pref) {
    if (div(t)) {
      stack_2.push(t - '0');
    } else if (opera(t)) {
      int u = stack_2.get();
      stack_2.pop();
      int o = stack_2.get();
      stack_2.pop();
      switch (t) {
        case '+':
          stack_2.push(u + o); break;
        case '-':
          stack_2.push(o - u); break;
        case '*':
          stack_2.push(u * o); break;
        case '/':
          stack_2.push(o / u); break;
        default:
          continue;
      }
    } else {
      continue;
    }
  }
  return stack_2.get();
}
