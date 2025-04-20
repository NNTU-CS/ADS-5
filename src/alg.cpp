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
  int count_p = 0;
  char str[100] = { 0 };
  while (inf[len] != '\0') {
    len += 1;
  }
  for (int count = 0; count < len; count++) {
    if (inf[count] >= '0' && inf[count] <= '9') {
      str[count_p] = inf[count];
      count_p += 1;
      str[count_p] = ' ';
      count_p += 1;
    } else if (inf[count] == '(') {
      stack.push(inf[count]);
    } else if (inf[count] == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        str[count_p] = stack.get();
        count_p += 1;
        str[count_p] = ' ';
        count_p += 1;
        stack.pop();
      }
      if (!stack.isEmpty()) {
        stack.pop();
      }
    } else {
      while (!stack.isEmpty() && prioritet(stack.get()) >= prioritet(inf[count]) ) {
        str[count_p] = stack.get();
        count_p += 1;
        str[count_p] = ' ';
        count_p += 1;
        stack.pop();
      }
      stack.push(inf[count]);
    }
  }
  while (!stack.isEmpty()) {
    str[count_p] = stack.get();
    count_p += 1;
    stack.pop();
    if (!stack.isEmpty()) {
      str[count_p] = ' ';
      count_p += 1;
    }
  }
  std::string pref = str;
  return pref;
}

int eval(const std::string& pref) {
  TStack<int, 100>stack;
  int len = 0;
  int count_p = 0;
  char str[100] = { 0 };
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
    } else if (pref[count] == '*') {
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
