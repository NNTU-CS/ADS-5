// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int foo(char x) {
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
std::string k1, k2;
TStack<char, 100>stack1;
for (auto& x : inf) {
  int p = foo(x);
  if (p == -1) {
    k1 = k1 + x + ' ';
  } else {
    char elem = stack1.get();
    if (p == 0 || foo(elem) < p || stack1.isEmpty()) {
      stack1.push(x);
    } else {
      if (x == ')') {
        while (foo(elem) >= p) {
          k1 = k1 + elem + ' ';
          stack1.pop();
          elem = stack1.get();
        }
        stack1.pop();
      } else {
        while (foo(elem) >= p) {
          k1 = k1 + elem + ' ';
          stack1.pop();
          elem = stack1.get();
        }
        stack1.push(x);
      }
    }
  }
}
while (!stack1.isEmpty()) {
  k1 = k1 + stack1.get() + ' ';
  stack1.pop();
}
for (int i = 0; i < k1.size() - 1; i++)
  k2 += k1[i];
return k2;
return std::string("");
}
int foo1(const int& l, const int& m, const int& x) {
  switch (x) {
    case '+':
      return l + m;
    case '-':
      return l - m;
    case '*':
      return l * m;
    case '/':
      return l / m;
    default:
      return 0;
  }
}
int eval(std::string pref) {
TStack<int, 100> stack1;
std::string r = "";
for (int i = 0; i < pref.size(); i++) {
  char elem = pref[i];
  if (foo(elem) == -1) {
    if (pref[i] == ' ') {
      continue;
    } else if (isdigit(pref[i+1])) {
      r += pref[i];
      continue;
    } else {
      r += pref[i];
      stack1.push(atoi(rez.c_str()));
      r = "";
    }
  } else {
    int m = stack1.get();
    stack1.pop();
    int l = stack1.get();
    stack1.pop();
    stack1.push(foo1(l, m, elem));
  }
}
return stack1.get();
}
