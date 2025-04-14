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
      stack1.push(c);
      flag = false;
    } else if (c == ')') {
      while (!stack1.isEmpty() && stack1.peek() != '(') {
        finall << ' ' << stack1.pop();
      }
      if (stack1.isEmpty()) {
        throw std::invalid_argument("There is no pair");
      }
      stack1.pop();
      flag = true;
    } else if (opperator(c)) {
      while (!stack1.isEmpty() && prioritet(c) <= prioritet(stack1.peek())) {
        finall << ' ' << stack1.pop();
      }
      stack1.push(c);
      flag = true;
    } else {
      throw std::invalid_argument("Invalid character");
    }
  }
  while (!stack1.isEmpty()) {
    if (stack1.peek() == '(') {
      throw std::invalid_argument("There is no pair");
    }
    finall << ' ' << stack1.pop();
  }
  return finall;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack2;
  std::istringstream stream(post);
  std::string token;
     while (stream >> token) {
      if (std::isdigit(token[0])) {
        int number = std::stoi(token);
        stack2.push(number);
      } else if (operator(token[0]) && token.size() == 1) {
        if (stack2.isEmpty()) {
          throw std::invalid_argument("Emptiness");
        }
        int oper2 = stack2.pop();
        if (stack2.isEmpty()) {
          throw std::invalid_argument("Emptiness");
        }
        int oper1 = stack2.pop();
        switch (token[0]) {
          case '+': stack2.push(oper1 + oper2); break;
          case '-': stack2.push(oper1 - oper2); break;
          case '*': stack2.push(oper1 * oper2); break;
          case '/':
            if (oper2 == 0) {
              throw std::runtime_error("ERROR");
            }
            stack2.push(oper1 / oper2);
            break;
        }
      } else {
        throw std::invalid_argument("Invalid token");
      }
    }
    if (stack2.isEmpty()) {
      throw std::invalid_argument("Emptiness");
    }
    int result = stack2.pop();
    if (!stack2.isEmpty()) {
      throw std::invalid_argument("Very much");
    }
  return result;
}
