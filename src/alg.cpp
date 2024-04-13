// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char sym) { 
  switch (sym) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    default: return -1;
  }
}

bool isNum(char sym){
  return '0' <= sym & sym <= '9';
}

TStack<char, 100> stack1;
TStack<int, 100> stack2;

std::string infx2pstfx(std::string inf) {
  std::string res;

  for (auto sym : inf) {
    if (isNum(sym)) {
      res = res + sym + ' ';
    } else if (sym == '(' || prioritet(stack1.peek()) < prioritet(sym) || stack1.isEmpty()) {
      stack1.push(sym);
    } else if (stack1.isEmpty()) {
      stack1.push(sym);
    } else if (prioritet((sym) <= prioritet(stack1.peek()))) {
      while(prioritet(stack1.peek() <= prioritet(sym))) {
        res = res + ' ' + stack1.peek();
        stack1.pop();
      } 
    } else if (sym == ')') {
      while (stack1.peek() != '(') {
        res = res + ' ' + stack1.peek();
        stack1.pop();
      }
    }
    }
    while (!(stack1.isEmpty())) {
      res = res + ' ' + stack1.peek();
      stack1.pop();
    }
  return res;
  }

int eval(std::string pref) {
  // добавьте код
  return 0;
}
