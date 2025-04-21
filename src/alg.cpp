// Copyright 2025 NNTU-CS
#include <cctype>
#include <string>
#include <map>
#include "tstack.h"

template<typename T, int size>
std::string TStack<T, size>::infx2pstfx(const std::string& inf) {
  std::string currentNumber = "";
  for (char c : inf) {
    if (isdigit(c)) {
      currentNumber += c;
      continue;
    }
    else {
      if (!currentNumber.empty()) {
        res += currentNumber;
        res += ' ';
        currentNumber = "";
      }
    }

    if (c == '(') {
      stack += c;
    }
    else if (c == '*' || c == '/') {
      bool fl = false;
      if (!stack.empty()) {
        while (stack.back() == '*' || stack.back() == '/') {
          res += stack.back();
          res += ' ';
          stack.pop_back();
          fl = true;
        }
      }

      if (fl) {
        if (stack.back() == '(') {
          stack.pop_back();
        }
      }

      stack += c;
    }
    else if (c == '-' || c == '+') {
      bool fl = false;
      if (!stack.empty()) {
        while (stack.back() == '-' || stack.back() == '+' || stack.back() == '*' || stack.back() == '/') {
          res += stack.back();
          res += ' ';
          stack.pop_back();
          fl = true;
        }
      }

      if (fl) {
        if (stack.back() == '(') {
          stack.pop_back();
        }
      }

      stack += c;
    }
    else if (c == ')') {
      while (stack.back() != '(' && !stack.empty()) {
        res += stack.back();
        res += ' ';
        stack.pop_back();
      }

      if (stack.back() == '(') {
        stack.pop_back();
      }
    }
  }

  if (!currentNumber.empty()) {
    res += currentNumber;
    res += ' ';
  }

  while (!stack.empty()) {
    res += stack.back();
    res += ' ';
    stack.pop_back();
  }

  res.pop_back();

  return res;
}

template<typename T, int size>
int TStack<T, size>::eval(const std::string& pref) {
  int stack[size];
  int top = -1;

  int i = 0;
  while (i < pref.size()) {
    if (pref[i] == ' ') {
      i++;
    }

    if (pref[i] == '+' || pref[i] == '-' || pref[i] == '*' || pref[i] == '/') {
      if (top < 1) {
        exit(1);
      }
      
      int b = stack[top--];
      int a = stack[top--];

      char symbol = pref[i];
      if (symbol == '+') {
        stack[++top] = a + b; 
      }
      else if (symbol == '-') {
        stack[++top] = a - b; 
      }
      else if (symbol == '*') {
        stack[++top] = a * b; 
      }
      else {
        stack[++top] = a / b; 
      }

      i++;
    }
    else if (isdigit(pref[i])) {
      int num = 0;
      while (i < pref.size() && isdigit(pref[i])) {
        num = num * 10 + (pref[i] - '0');
        i++;
      }

      stack[++top] = num;
    }
  }

  if (top != -1) {
    return stack[top];
  }
  else {
    exit(1);
  }
}

template class TStack<int, 100>;
