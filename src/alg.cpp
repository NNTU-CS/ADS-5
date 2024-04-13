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

int getPriority(char sym) {
  if (sym == '(') {
    return 0;
  } else if (sym == ')') {
    return 1;
  } else if (sym == '+' || sym == '-') {
    return 2;
  } else if (sym == '*' || sym == '/') {
    return 3;
  } else {
    return -1;
  }
}

int operation(int a, int b, char sym) {
  switch (sym) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      return a / b;
  }
  return 0;
}

bool isOperator(char sym) {
  return sym == '+' || sym == '-' || sym == '*' || sym == '/';
}

bool isNum(char sym){
  return '0' <= sym & sym <= '9';
}


std::string infx2pstfx(std::string inf) {
  // добавьте код
  return std::string("");
  TStack<char, 100> stack;
  std::string res;
  int priority = 0;
  for (auto sym : inf) {
    int count = 1;
    if (isNum((sym))) {
      res += sym;
      if ((count != inf.length() - 1) || (!stack.isEmpty())) {
        res += " ";
      }
    } else if (sym == '(') {
      stack.push(sym);
    } else if (stack.isEmpty()) {
      stack.push(sym);
    } else if (sym == ')') {
      while (stack.stTop() != '(') {
        res += stack.pop();
        res += ' ';
      }
      stack.pop();
    } else if (getPriority(sym) <= getPriority(stack.stTop())) {
      while (getPriority(sym) <= getPriority(stack.stTop())) {
        res += stack.pop();
      }
      res += ' ';
      stack.push(sym);
    } else {
      stack.push(sym);
    }
    count ++;
  }
  while (!stack.isEmpty()) {
    res += stack.pop();
    if (!stack.isEmpty()) {
      res += ' ';
    }
  }
  return res;
}

int eval(std::string pref) {
  // добавьте код
  return 0;
  int num1 = 0, num2 = 0;
  TStack<int, 100> stack;
  std::string line;
  for (auto sym : pref) {
    if (sym >= '0' && sym <= '9') {
      line += sym;
    } else if (sym == ' ' && line.length() > 0) {
      stack.push(std::stoi(line));
      line = "";
    } else if (isOperator(sym)) {
      num2 = stack.pop();
      num1 = stack.pop();
      stack.push(operation(num1, num2, sym));
    }
  }
  return stack.pop();
}

