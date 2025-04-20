// Copyright 2025 NNTU-CS
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include "tstack.h"

int precedence(char op) {
  if (op == '*' || op == '/') return 2;
  if (op == '+' || op == '-') return 1;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string op;
  std::string tek; 
  for (size_t i = 0; i < inf.length(); ++i) {
    char current = inf[i];
    if (std::isdigit(current)) {
    tek.clear();
    while (i < inf.length() && std::isdigit(inf[i])) {
      tek += inf[i];
      i++;
    }
    i--; 
    op += tek + ' '; 
    }
    else if (current == '(') {
      stack.dob('(');
    }
    else if (current == ')') {
      while (!stack.nepol() && stack.pe() != '(') {
        op += stack.dl();
        op += ' ';
      }
      if (!stack.nepol()) stack.dl(); 
    }
    else { 
      while (!stack.nepol() && precedence(stack.pe()) >= precedence(current)) {
        op += stack.dl();
        op += ' ';
      }
      stack.dob(current);
    }
  }
  while (!stack.nepol()) {
    op += stack.dl();
    op += ' ';
  }
  if (!op.empty() && op.back() == ' ') {
    op.erase(op.size() - 1);
  }
  return op;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack;
  std::istringstream iz(pref);
  std::string tek;
  while (iz >> tek) {
    if (std::isdigit(tek[0])) {
      stack.dob(std::stoi(tek));
    }
    else {
      int right = stack.dl();
      int left = stack.dl();
      switch (tek[0]) {
      case '-':
        stack.dob(left - right);
        break;
      case '+':
        stack.dob(left + right);
        break;
      case '/':
        stack.dob(left / right);
        break;
      case '*':
        stack.dob(left * right);
        break;
      default:
        throw std::invalid_argument("Error");
      }
      }
    }
    return stack.dl();
}
