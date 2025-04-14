// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "tstack.h"

int prioritet(char op) {
  switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

bool opperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack1;
  std::ostringstream finall;
  bool flag = false;
  for (size_t i = 0; i < inf.size(); ++i) {
    const char c = inf[i];
    if (std::isspace(c)) continue;
    if (std::isdigit(c)) {
      if (flag) {
        finall << ' ';
      }
      finall << c;
      flag = true;
    } else if (c == '(') {
      opStack.push(c);
      flag = false;
    } else if (c == ')') {
      while (!opStack.isEmpty() && opStack.peek() != '(') {
        finall << ' ' << opStack.pop();
      }
      if (opStack.isEmpty()) {
        throw std::invalid("There is no pair");
      }
      opStack.pop();
      flag = true;
    } else if (opperator(c)) {
      while (!opStack.isEmpty() && prioritet(c) <= prioritet(opStack.peek())) {
        finall << ' ' << opStack.pop();
      }
      opStack.push(c);
      flag = true;
    } else {
      throw std::invalid("Invalid character");
    } 
  }
  while (!opStack.isEmpty()) {
    if (opStack.peek() == '(') {
      throw std::invalid("There is no pair");
    }
    finall << ' ' << opStack.pop();
  }
  return finall;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack2;
  std::istringstream stream(post);
  std::string token;
  while(stream >> token) {
    if (std::isdigit(token[0])) {
      int number = std::stoi(token);
      numStack.push(number);
    } else if(operator(token[0]) && token.size() == 1) {
      if (numStack.isEmpty()) {
        throw std::invalid("Emptiness");
      }
      int oper2 = numStack.pop();
      if (numStack.isEmpty()) {
        throw std::invalid("Emptiness");
      }
      int oper1 = numStack.pop();
      switch (token[0]) {
        case '+': numStack.push(oper1 + oper2); break;
        case '-': numStack.push(oper1 - oper2); break;
        case '*': numStack.push(oper1 * oper2); break;
        case '/':
          if (oper2 == 0) {
            throw std::error("ERROR");
          }
          numStack.push(oper1 / oper2);
          break;
      }
    } else {
      throw std::invalid("Invalid token");
    }
  }
  if (numStack.isEmpty()) {
    throw std::invalid("Emptiness");
  }
  int result = numStack.pop();
  if (!numStack.isEmpty()) {
    throw std::invalid("Very much");
  }
  return result;
}
