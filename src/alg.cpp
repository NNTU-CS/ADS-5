// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> opStack;
  std::string result;
  int i = 0;
  while (i < inf.size()) {
    if (isdigit(inf[i])) {
      while (i < inf.size() && isdigit(inf[i])) {
        result += inf[i];
        i++;
      }
      result += ' ';
    } else if (inf[i] == '(') {
      opStack.push('(');
      i++;
    } else if (inf[i] == ')') {
      while (!opStack.isEmpty() && opStack.top() != '(') {
        result += opStack.pop();
        result += ' ';
      }
      opStack.pop();
      i++;
    } else if (inf[i] == '+' || inf[i] == '-' || inf[i] == '*' || inf[i] == '/') {
      while (!opStack.isEmpty() && priority(opStack.top()) >= priority(inf[i])) {
        result += opStack.pop();
        result += ' ';
      }
      opStack.push(inf[i]);
      i++;
    } else {
      i++;
    }
  }
  while (!opStack.isEmpty()) {
    result += opStack.pop();
    result += ' ';
  }
  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> valStack;
  std::stringstream ss(post);
  std::string token;
  while (ss >> token) {
    if (isdigit(token[0])) {
      valStack.push(std::stoi(token));
    } else if (token.size() == 1 && std::string("+-*/").find(token[0]) != std::string::npos) {
      int b = valStack.pop();
      int a = valStack.pop();
      int result = 0;
      switch (token[0]) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/':
          if (b == 0) throw std::runtime_error("division by zero");
          result = a / b;
          break;
      }
      valStack.push(result);
    }
  }
  return valStack.pop();
}
