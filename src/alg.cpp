// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPriority(char operation) {
  switch (operation) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    default: return -1;
  }
}

std::string infx2pstfx(std::string inf) {
  std::string Res, Res1;
  TStack<char, 100>Stack1;
  for (auto& x : inf) {
    int p = getPriority(x);
    if (p == -1) {
      Res = Res + x + ' ';
    } else {
      char element = Stack1.get();
      if (p == 0 || getPriority(element) < p || Stack1.isEmpty()) {
        Stack1.push(x);
      } else {
        if (x == ')') {
          while (getPriority(element) >= p) {
            Res = Res + element + ' ';
            Stack1.pop();
            element = Stack1.get();
          }
          Stack1.pop();
        } else {
          while (getPriority(element) >= p) {
            Res = Res + element + ' ';
            Stack1.pop();
            element = Stack1.get();
          }
          Stack1.push(x);
        }
      }
    }
  }
  while (!Stack1.isEmpty()) {
    Res = Res + Stack1.get() + ' ';
    Stack1.pop();
  }
  for (int i = 0; i < Res.size() - 1; i++)
    Res1 += Res[i];
  return Res1;
}

int doMath(const int& p, const int& v, const int& x) {
  switch (x) {
    case '+': return p + v;
    case '-': return p - v;
    case '/': return p / v;
    case '*': return p * v;
    default: return 0;
  }
}

int eval(std::string pref) {
  TStack<int, 100> Stack1;
  std::string Res = "";
  for (int i = 0; i < pref.size(); i++) {
    char element = pref[i];
    if (getPriority(element) == -1) {
      if (pref[i] == ' ') {
        continue;
      } else if (isdigit(pref[i+1])) {
        Res += pref[i];
        continue;
      } else {
        Res += pref[i];
        Stack1.push(atoi(rez.c_str()));
        Res = "";
      }
    } else {
      int v = Stack1.get();
      Stack1.pop();
      int p = Stack1.get();
      Stack1.pop();
      Stack1.push(doMath(p, v, element));
    }
  }
  return Stack1.get();
}
