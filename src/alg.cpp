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
  int count = 0;
  for (auto& sym : inf) {
    if (isNum(sym)) {
      count++;
      if (count == 1){
        res = res + sym + ' ';
      }
    } else if (sym == '(') {
      stack1.push(sym);
    } else if(prioritet(sym) > prioritet(stack1.peek())) {
      stack1.push(sym);
    } else if(stack1.isEmpty()) {
      stack1.push(sym);
    } else if(sym == ')') {
      while (stack1.peek() != '(') {
        res = res + ' ' + stack1.peek();
        stack1.pop();
      }
      stack1.pop();
    } else {
      while (!stack1.isEmpty() && (prioritet(sym) <= prioritet(stack1.peek()))) {
        res = res + ' ' + stack1.peek();
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
  int num1 = 0;
  int num2 = 0;
  for (auto sym : pref) {
    if (isNum(sym)) {
      stack2.push(sym - '0');
    }
    else if (!isNum(sym)) {
      int num1 = stack2.peek();
      stack2.pop();
      int num2 = stack2.peek();
      stack2.pop();
     }
     switch (sym) {
      case '+': 
        stack2.push(num1 + num2);
        break;
        case '-': 
        stack2.push(num1 - num2);
        break;
        case '*': 
        stack2.push(num1 * num2);
        break;
        case '/': 
        stack2.push(num1 / num2);
        break;
      default: continue;
      }
      return stack2.peek();
  }
  return 0;
}
