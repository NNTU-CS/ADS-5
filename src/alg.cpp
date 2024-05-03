// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int Priority(char c) {
  if (c == '(')
    return 0;
  else if (c == ')')
    return 1;
  else if (c == '+' || c == '-')
    return 2;
  else if (c == '*' || c == '/')
    return 3;
  else
    return -1;
}
std::string infx2pstfx(std::string inf) {
  std::string p;
  TStack<char, 100> stack1;
  for (char c : inf) {
    if (Priority(c) == -1) {
      p += c;
      p += ' ';
    } else {
        if (c == ')') {
          while (stack1.get() != '(') {
            p += stack1.pop();
            p += ' ';
          }
          stack1.pop();
        } else if (c == '(' || stack1.isEmpty()) {
            stack1.push(c);
          } else if (!stack1.isEmpty()) {
              char elem = stack1.get();
              if (Priority(elem) < Priority(c)) {
                stack1.push(c);
              } else {
                  while (Priority(elem) >= Priority(c) && !stack1.isEmpty()) {
                    post += stack1.pop();
                    post += ' ';
                  }
                  stack1.push(c);
                }
            }
      }
  }
  while (!stack1.isEmpty()) {
    p += stack1.pop();
    p += ' ';
  }
  p.pop_back();
  return p;
}
  int eval(std::string p) {
  TStack<int, 100> stack2;
  std::string number;
  for (int i = 0; i < p.size(); ++i) {
    if (Priority(p[i]) == -1) {
      if (p[i] == ' ') {
        continue;
      } else if (isdigit(p[i + 1])) {
          number += p[i];
          continue;
        } else {
            number += p[i];
            int value = atoi(number.c_str());
            stack2.push(value);
            number = "";
          }
    } else {
        int b = stack2.pop();
        int a = stack2.pop();
        switch (p[i]) {
        case '+':
          stack2.push(a + b);
          break;
        case '-':
          stack2.push(a - b);
          break;
        case '*':
          stack2.push(a * b);
          break;
        case '/':
          stack2.push(a / b);
          break;
        }
      }
  }
  return stack2.get();
  }
