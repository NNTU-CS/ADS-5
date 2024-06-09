// Copyright 2021 NNTU-CS
#include <math.h>
#include <string>
#include <map>
#include "tstack.h"

int ToInt(const std::string& str) {
  int size = str.size();
  int res = 0;
  for (int i = 0; str[i]; i++) {
    res += (pow(10, size - 1)) * (str[i]-'0');
    size--;
  }
  return res;
}
int Operation(int num1, int num2, char sym) {
  switch (sym) {
  case '+':
    return num1 + num2;
  case '-':
    return num1 - num2;
  case '*':
    return num1 * num2;
  case '/':
    return num1 / num2;
  }
  return 0;
}
int Priority(char sym) {
  if (sym == '(')
    return 0;
  else if (sym == ')')
    return 1;
  else if (sym == '+' || sym == '-')
    return 2;
  else if (sym == '/' || sym == '*')
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
      prior = Priority(inf[i]);
      if (inf[i] == ')') {
        while (stack.ViewTop() != '(') {
          pref+= stack.Pop();
          pref += ' ';
        }
        stack.Pop();
      } else if (prior == 0 || prior > Priority(stack.ViewTop())
        || stack.ViewTop() == -1) {
        stack.Push(inf[i]);
      } else if (Priority(stack.ViewTop()) >= prior) {
          while (Priority(stack.ViewTop()) >= prior) {
              pref += stack.Pop();
          }
          pref += ' ';
          stack.Push(inf[i]);
      }
    }
  }
  while (stack.ViewTop() != -1) {
    pref += stack.Pop();
    pref += ' ';
  }
  pref.pop_back();
  return pref;
}

int eval(std::string pref) {
  std::string fake;
  int num1 = 0, num2 = 0;
  TStack<int, 100> stack;
  for (int i = 0; pref[i]; i++) {
    if (pref[i] >= '0' && pref[i] <= '9') {
      while (pref[i] >= '0' && pref[i] <= '9') {
        fake += pref[i++];
      }
      stack.Push(ToInt(fake));
      fake = "";
    } else if (pref[i] == ' ') {
      continue;
    } else {
      num1 = stack.Pop();
      num2 = stack.Pop();
      stack.Push(Operation(num2, num1, pref[i]));
    }
  }
  return stack.Pop();
}
