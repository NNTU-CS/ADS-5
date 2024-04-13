// Copyright 2021 NNTU-CS
#include <map>
#include "tstack.h"

int Prioritet(char x) {
  switch (x) {
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
  std::string rezult, rez1;
  TStack<char, 100>stack1;
  for (auto& x : inf) {
    int pri = Prioritet(x);
    if (pri == -1) {
      rezult = rezult + x + ' ';
    } else {
      char elem = stack1.get();
      if (pri == 0 || Prioritet(elem) < pri || stack1.isEmpty()) {
        stack1.push(x);
      } else {
        if (x == ')') {
          while (Prioritet(elem) >= pri) {
            rezult = rezult + elem + ' ';
            stack1.pop();
            elem = stack1.get();
          }
          stack1.pop();
        } else {
          while (Prioritet(elem) >= pri) {
            rezult = rezult + elem + ' ';
            stack1.pop();
            elem = stack1.get();
          }
          stack1.push(x);
        }
      }
    }
  }
  while (!stack1.isEmpty()) {
    rezult = rezult + stack1.get() + ' ';
    stack1.pop();
  }
  for (int i = 0; i < rezult.size() - 1; i++)
    rez1 += rezult[i];
  return rez1;
}

int schet(const int& p, const int& v, const int& x) {
  switch (x) {
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
  std::string rezult = "";
  for (int i = 0; i < pref.size(); i++) {
    char elem = pref[i];
    if (Prioritet(elem) == -1) {
      if (pref[i] == ' ') {
        continue;
      } else if (isdigit(pref[i+1])) {
        rezult += pref[i];
        continue;
      } else {
        rezult += pref[i];
        stack1.push(atoi(rezult.c_str()));
        rezult = "";
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
