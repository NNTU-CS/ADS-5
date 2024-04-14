// Copyright 2021 NNTU-CS
#include <math.h>
#include <string>
#include <map>
#include "tstack.h"

int ToInt(const std::string& str) {
  int size = str.size();
  int it = 0;
  for (int i = 0; str[i]; i++) {
    it += (pow(10, size - 1)) * (str[i]-'0');
    size--;
  }
  return it;
}
int znaki(int a, int b, char chislo) {
  switch (chislo) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  }
  return 0;
}
int priora(char chislo) {
  if (chislo == '(')
    return 0;
  else if (chislo == ')')
    return 1;
  else if (chislo == '+' || chislo == '-')
    return 2;
  else if (chislo == '/' || chislo == '*')
    return 3;
  else
    return -1;
}
std::string infx2pstfx(std::string inf) {
  bool flag = 0;
  TStack<char, 100> stack;
  std::string pref;
  int prior = 0;
  for (int i = 0; inf[i]; i++) {
    if (inf[i] >= '0' && inf[i] <= '9') {
      pref += inf[i];
      if (inf[i+1] < '0' || inf[i+1] > '9') {
        pref += ' ';
      }
      flag = 1;
    } else if (inf[i] != '\0') {
      prior = priora(inf[i]);
      if (inf[i] == ')') {
        while (stack.see() != '(') {
          pref+= stack.rok();
          pref += ' ';
        }
        stack.rok();
      } else if (prior == 0 || prior > priora(stack.see())
        || stack.see() == -1) {
        stack.map(inf[i]);
      } else if (priora(stack.see()) >= prior) {
          while (priora(stack.see()) >= prior) {
              pref += stack.rok();
          }
          pref += ' ';
          stack.map(inf[i]);
      }
    }
  }
  while (stack.see() != -1) {
    pref += stack.rok();
    pref += ' ';
  }
  pref.pop_back();
  return pref;
}
int eval(std::string pref) {
  std::string fake;
  int a = 0, b = 0;
  TStack<int, 100> stack;
  for (int i = 0; pref[i]; i++) {
    if (pref[i] >= '0' && pref[i] <= '9') {
      while (pref[i] >= '0' && pref[i] <= '9') {
        fake += pref[i++];
      }
      stack.map(ToInt(fake));
      fake = "";
    } else if (pref[i] == ' ') {
      continue;
    } else {
      a = stack.rok();
      b = stack.rok();
      stack.map(znaki(b, a, pref[i]));
    }
  }
  return stack.rok();
}
