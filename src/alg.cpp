// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include "tstack.h"

int priority(char symb) {
  if (symb == '+' || symb == '-') return 1;
  if (symb == '*' || symb == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> opList;
  std::ostringstream result;
  size_t index = 0;

  while (index < inf.size()) {
    char ch = inf[index];
    if (std::isdigit(ch)) {
      while (index < inf.size() && std::isdigit(inf[index])) {
        result << inf[index++];
      }
      result << ' ';
      index--;
    } else if (ch == '(') {
      opList.add(ch);
    } else if (ch == ')') {
      while (!opList.isVoid() && opList.getTop() != '(') {
        result << opList.remove() << ' ';
      }
      if (!opList.isVoid()) {
        result << opList.remove();
      }
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      while (!opList.isVoid() && priority(opList.getTop()) >= priority(ch)) {
        result << opList.remove() << ' ';
      }
      opList.add(ch);
    }
    index++;
  }

  while (!opList.isVoid()) {
    result << opList.remove() << ' ';
  }
  std::string output = result.str();
  if (!output.empty() && output.back == ' ') {
    output.pop_back();
  }
  return output;
}

int eval(const std::string& pref) {
  TStack<int, 100> vals
  std::istringstream iss(pref);
  std::string part;

  while (iss >> part) {
    if (std::isdigit(part[0])) {
      vals.add(std::stoi(part));
    } else {
      int right = vals.remove();
      int left = vals.remove();
      switch (part[0]) {
        case '+': vals.add(left + right); break;
        case '-': vals.add(left - right); break;
        case '*': vals.add(left * right); break;
        case '/': vals.add(left / right); break;
      }
    }
  }
  return vals.remove();
}
