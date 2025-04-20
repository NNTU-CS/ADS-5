// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char oper) {
  switch (oper) {
  case '+':
    return 1;
  case '-':
    return 1;
  case '*':
    return 2;
  case '/':
    return 2;
  default:
    return 0;
  }
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100>stack;
  int len = 0;
  std::string pref;
  while (inf[len] != '\0') {
    len += 1;
  }
  for (int count = 0; count < len; count++) {
    if (inf[count] >= '0' && inf[count] <= '9') {
      pref += inf[count];
      pref += ' ';
    } else if (inf[count] == '(') {
      stack.push(inf[count]);
    } else if (inf[count] == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        pref += stack.get();
        pref += ' ';
        stack.pop();
      }
      if (!stack.isEmpty()) {
        stack.pop();
      }
    } else {
      while (!stack.isEmpty() && 
        prioritet(stack.get()) >= prioritet(inf[count])) {
        pref += stack.get();
        pref += ' ';
        stack.pop();
      }
      stack.push(inf[count]);
    }
  }
  while (!stack.isEmpty()) {
    pref += stack.get();
    stack.pop();
    if (!stack.isEmpty()) {
      pref += ' ';
    }
  }
  return pref;
}

int eval(const std::string& pref) {
  TStack<int, 100>stack;
  int len = 0;
  while (pref[len] != '\0') {
    len += 1;
  }
  for (int count = 0; count < len; count++) {
    if (pref[count] >= '0' && pref[count] <= '9') {
      stack.push(pref[count]-'0');
    } else if (pref[count] == '+') {
      int right = stack.get();
      stack.pop();
      int left = stack.get();
      stack.pop();
      int final = left + right;
      stack.push(final);
    } else if (pref[count] == '-') {
      int right = stack.get();
      stack.pop();
      int left = stack.get();
      stack.pop();
      int final = left - right;
      stack.push(final);
    } else if (pref[count] == '*' ) {
      int right = stack.get();
      stack.pop();
      int left = stack.get();
      stack.pop();
      int final = left * right;
      stack.push(final);
    } else if (pref[count] == '/') {
      int right = stack.get();
      stack.pop();
      int left = stack.get();
      stack.pop();
      int final = left / right;
      stack.push(final);
    }
  }
  return stack.get();
}
