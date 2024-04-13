// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::map <char, int> prioritet 
{ 
  std::make_pair('(', 0), 
  std::make_pair(')', 1),
  std::make_pair('+', 2),
  std::make_pair('-', 2),
  std::make_pair('*', 3),
  std::make_pair('/', 3)
};

bool isNum(char sym){
  switch (sym) {
  case '0': return true;
  case '1': return true;
  case '2': return true;
  case '3': return true;
  case '4': return true;
  case '5': return true;
  case '6': return true;
  case '7': return true;
  case '8': return true;
  case '9': return true;
  default: return false;
  }
}

TStack<char, 100> stack1;
TStack<int, 100> stack2;

std::string infx2pstfx(std::string inf) {
  std::string res;
  for (auto sym : inf) { 
    if (isNum(sym)) {
      res += sym;
    } else if (sym == '(' || (prioritet[stack1.peek()] < prioritet[sym]) || stack1.isEmpty())  { 
      stack1.push(sym);
      if (prioritet[stack1.peek()] >= prioritet[sym]) { 
        while (!(stack1.isEmpty())){
          res += stack1.peek();
          stack1.pop();
        }
        stack1.push(sym);
      }
    } else if (sym == ')') { 
      while (stack1.peek() != '(') { 
        res += stack1.peek();
        stack1.pop();
      }
      stack1.pop();
    }
  }
  while (!(stack1.isEmpty())) {
    res += stack1.peek();
    stack1.pop();
    }
  return res;
}

int eval(std::string pref) {
  // добавьте код
  return 0;
}
