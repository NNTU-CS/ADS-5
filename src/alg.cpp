// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isSign(char sym) { 
  if (('0' <= sym && sym <= '9') || sym == ' ') return false;
  return true;
}
int ctoi(const char sym) {
  if ('0' <= sym && sym <= '9') {
    switch (sym) { 
    case '0':
      return 0;
      break;
    case '1':
      return 1;
      break;
    case '2':
      return 2;
      break;
    case '3':
      return 3;
      break;
    case '4':
      return 4;
      break;
    case '5':
      return 5;
      break;
    case '6':
      return 6;
      break;
    case '7':
      return 7;
      break;
    case '8':
      return 8;
      break;
    case '9':
      return 9;
      break;
    default:
      return -1;
      break;
    }
  }
}
int operation(int f, int s, char sign) {
  switch (sign) { 
  case '+':
    return f + s;
    break;
  case '-':
    return f - s;
    break;
  case '*':
    return f * s;
    break;
  case '/':
    return f / s;
    break;
  default:
    return 0;
    break;
  }
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::map<char, int> operations;
  std::string in(inf);
  std::string out = "";
  operations['('] = 0;
  operations[')'] = 1;
  operations['+'] = 2;
  operations['-'] = 2;
  operations['*'] = 3;
  operations['/'] = 3;
  for (int i = 0; i < in.size(); i++) {
    if ('0' <= in[i] && in[i] <= '9') {
      out += in[i];
      out += " ";
      continue;
    }
    if (isSign(in[i])) {
      if (stack.isEmpty()) {
        stack.push(in[i]);
      } else {
        if (operations[in[i]] == 0) {
          stack.push(in[i]);
        } else {
          if (in[i] == ')') {
            while ((!(stack.isEmpty())) && (stack.get() != '(')) {
              out += stack.get();
              out += " ";
              stack.pop();
            }
            stack.pop();
          }
          else if (operations[in[i]] > operations[stack.get()]) {
            stack.push(in[i]);
          } else {
            while (!(stack.isEmpty())) {
              out += stack.get();
              out += " ";
              stack.pop();
            }
            stack.push(in[i]);
          }
        }

      }
    }
  }
  if (!(stack.isEmpty())) {
    while (!(stack.isEmpty())) {
      out += stack.get();
      out += " ";
      stack.pop();
    }
  }
  return out;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack;
  std::string in(pref);
  for (int i = 0; i < in.size(); i++) {
    if ('0' <= in[i] && in[i] <= '9') {
      int cur = ctoi(in[i]);
      stack.push(cur);
      continue;
    } else if (isSign(in[i])) {
      int second = stack.get();
      stack.pop();
      int first = stack.get();
      stack.pop();
      int res = operation(first, second, in[i]);
      stack.push(res);
    }
  }
  return stack.get();
}
