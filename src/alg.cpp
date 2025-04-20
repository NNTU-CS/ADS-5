// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include <map>
#include "tstack.h"

int GetPriority(char ope) {
  if (ope == '+' || ope == '-') return 1;
  if (ope == '*' || ope == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string reS;
  std::string numm;

  for (char c : inf) {
    if (isdigit(c)) {
      numm += c;
    } else {
      if (!numm.empty()) {
        reS += numm + ' ';
        numm.clear();
      }

      if (c == '(') {
        stack.Push(c);
      } else if (c == ')') {
        while (!stack.IsEmpty() && stack.Top() != '(') {
          reS += stack.Pop();
          reS += ' ';
        }
        if (!stack.IsEmpty()) {
          stack.Pop();
        }
      } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        while (!stack.IsEmpty() && GetPriority(stack.Top()) >= GetPriority(c)) {
          reS += stack.Pop();
          reS += ' ';
        }
        stack.Push(c);
      }
    }
  }

  if (!numm.empty()) {
    reS += numm + ' ';
  }

  while (!stack.IsEmpty()) {
    reS += stack.Pop();
    reS += ' ';
  }

  if (!reS.empty() && reS.back() == ' ') {
    reS.pop_back();
  }

  return reS;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::string numm;

  for (size_t i = 0; i < post.size(); ++i) {
    char c = post[i];
    if (isdigit(c)) {
      numm += c;
    } else if (c == ' ' && !numm.empty()) {
      stack.Push(std::stoi(numm));
      numm.clear();
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      int b = stack.Pop();
      int a = stack.Pop();
      int resu = 0;
      switch (c) {
        case '+': resu = a + b; break;
        case '-': resu = a - b; break;
        case '*': resu = a * b; break;
        case '/': resu = a / b; break;
      }
      stack.Push(resu);
    }
  }

  if (!numm.empty()) {
    stack.Push(std::stoi(numm));
  }

  return stack.Pop();
}
