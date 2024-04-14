// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prio(char);
int score(int, int, char);
std::string infx2pstfx(std::string);
int eval(std::string);

std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack;
  std::string line = "";
  bool flag = false;
  try {
    for (char& k : inf) {
      if ((k >= '0') && (k <='9')) {
        if (flag) {
          line = line + " " + k;
          flag = false;
        } else {
          line = line + k;
        }
      } else {
        if (k == '(') {
          stack.PushUp(k);
        } else {
          flag = true;
          if (stack.IfZero()) {
            stack.PushUp(k);
          } else {
            if (k == ')') {
              while (stack.ElemUp() != '(') {
                line = line + " " + stack.PopBack();
              }
              stack.PopBack();
            } else {
              if (prio(k) > prio(stack.ElemUp())) {
                stack.PushUp(k);
              } else {
                while ((!stack.IfZero()) &&
                  (prio(k) <= prio(stack.ElemUp()))) {
                  line = line + " " + stack.PopBack();
                }
                stack.PushUp(k);
              }
            }
          }
        }
      }
    }
    while (!stack.IfZero()) {
      line = line + " " + stack.PopBack();
    }
    return line;
  }
  catch (std::string error) {
    return "fall!";
  }
}

int eval(std::string pref) {
  std::string line = "";
  TStack<int, 100> stack1;
  bool flag = false;
  try {
    for (char& s : pref) {
      if (!flag) {
        if (('0' <= s) && (s <= '9')) {
          line += s;
        } else {
          if (line == "") {
            int i = stack1.PopBack();
            int j = stack1.PopBack();
            int k = score(j, i, s);
            stack1.PushUp(k);
            flag = true;
          } else {
            stack1.PushUp(stoi(line));
            line = "";
          }
        }
      } else {
        flag = false;
      }
    }
    return stack1.PopBack();
  }
  catch (std::string error) {
    return -1;
  }
  return 0;
}

int prio(char symbol) {
  int num = 0;
  switch (symbol) {
  case '+':
    return 2;
  case '-':
    return 2;
  case '(':
    return 0;
  case '*':
    return 3;
  case '/':
    return 3;
  case ')':
    return 1;
  default:
    break;
  }
  return num;
}
int score(int x, int y, char symbol) {
  switch (symbol) {
  case '+':
    return x + y;
  case '-':
    return x - y;
  case '*':
    return x * y;
  case '/':
    return x / y;
  default:
    return 0;
  }
}
