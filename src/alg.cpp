// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"
int priority(char oper) {
  if (oper == '+' || oper == '-') return 1;
  if (oper == '*' || oper == '/') return 2;
  return 0;
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> opsList;
  std::ostringstream result;
  size_t index = 0;
  while (index < inf.size()) {
    char symbol = inf[index];
    if (std::isdigit(symbol)) {
      while (index < inf.size() && std::isdigit(inf[index])) {
        result << inf[index++];
      }
      result << ' ';
      --index;
    } else if (symbol == '(') {
      opsList.add(symbol);
    } else if (symbol == ')') {
      while (!opsList.isVoid() && opsList.getTop() != '(') {
        result << opsList.remove() << ' ';
      }
      if (!opsList.isVoid()) {
        opsList.remove();
      }
    } else if (symbol == '+' || symbol == '-' ||
               symbol == '*' || symbol == '/') {
      while (!opsList.isVoid() &&
             priority(opsList.getTop()) >= priority(symbol)) {
        result << opsList.remove() << ' ';
      }
      opsList.add(symbol);
    }
    ++index;
  }
  while (!opsList.isVoid()) {
    result << opsList.remove() << ' ';
  }
  std::string output = result.str();
  if (!output.empty() && output.back() == ' ')
    output.pop_back();
  return output;
}
int eval(const std::string& post) {
  TStack<int, 100> vals;
  std::istringstream iss(post);
  std::string part;
  while (iss >> part) {
    if (std::isdigit(part[0])) {
      vals.add(std::stoi(part));
    } else {
      int rhs = vals.remove();
      int lhs = vals.remove();
      switch (part[0]) {
        case '+': vals.add(lhs + rhs); break;
        case '-': vals.add(lhs - rhs); break;
        case '*': vals.add(lhs * rhs); break;
        case '/': vals.add(lhs / rhs); break;
      }
    }
  }
  return vals.remove();
}
