// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int Prior(char y) {
  switch (y) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+': case '-':
      return 2;
    case '*': case '/':
      return 3;
    default:
      return -1;
    }
}
std::string infx2pstfx(std::string inf) {
  std::string rez, rezult1;
  TStack<char, 100>stack1;
  for (auto& y : inf) {
    int p = Prior(y);
    if (p == -1) {
      rez = rez + y + ' ';
    } else {
      char elem = stack1.get();
      if (p == 0 || Prior(elem) < p || stack1.isEmpty()) {
        stack1.push(y);
      } else {
        if (y == ')') {
          while (Prior(elem) >= p) {
            rez = rez + elem + ' ';
            stack1.pop();
            elem = stack1.get();
          }
          stack1.pop();
        } else {
          while (Prior(elem) >= p) {
            rez = rez + elem + ' ';
            stack1.pop();
            elem = stack1.get();
          }
          stack1.push(y);
        }
      }
    }
  }
  while (!stack1.isEmpty()) {
    rez = rez + stack1.get() + ' ';
    stack1.pop();
  }
  for (int i = 0; i < rez.size() - 1; i++)
    rezult1 += rez[i];
  return rezult1;
}

int schet(const int& p, const int& v, const int& y) {
  switch (y) {
    case '+':
      return p + v;
    case '-':
      return p - v;
    case '/':
      return p / v;
    case '*':
      return p * v;
    default:
      return 0;
  }
}

int eval(std::string pref) {
  TStack<int, 100> stack1;
  std::string rez = "";
  for (int i = 0; i < pref.size(); i++) {
    char elem = pref[i];
    if (Prior(elem) == -1) {
      if (pref[i] == ' ') {
        continue;
      } else if (isdigit(pref[i+1])) {
        rez += pref[i];
        continue;
      } else {
        rez += pref[i];
        stack1.push(atoi(rez.c_str()));
        rez = "";
      }
    } else {
      int v = stack1.get();
      stack1.pop();
      int p = stack1.get();
      stack1.pop();
      stack1.push(schet(p, v, elem));
    }
  }
  return stack1.get();
}
