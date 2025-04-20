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
        stack.push(c);
      } else if (c == ')') {
        while (!stack.isEmpty() && stack.top() != '(') {
          reS += stack.pop();
          reS += ' ';
        }
        if (!stack.isEmpty()) {
          stack.pop();
        }
      } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        while (!stack.isEmpty() && GetPriority(stack.top()) >= GetPriority(c)) {
          reS += stack.pop();
          reS += ' ';
        }
        stack.push(c);
      }
    }
  }

  if (!numm.empty()) {
    reS += numm + ' ';
  }

  while (!stack.isEmpty()) {
    reS += stack.pop();
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
      stack.push(std::stoi(numm));
      numm.clear();
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      int b = stack.pop();
      int a = stack.pop();
      int resu = 0;
      switch (c) {
        case '+': resu = a + b; break;
        case '-': resu = a - b; break;
        case '*': resu = a * b; break;
        case '/': resu = a / b; break;
      }
      stack.push(resu);
    }
  }

  if (!numm.empty()) {
    stack.push(std::stoi(numm));
  }

  return stack.pop();
}
