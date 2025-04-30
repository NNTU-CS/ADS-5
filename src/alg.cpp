// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <stack>
//#include "tstack.h"

int priority(char symb) {
  if (symb == '+' || symb == '-') return 1;
  if (symb == '*' || symb == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  std::stack<char> opList;
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
      opList.push(ch);
    } else if (ch == ')') {
      while (!opList.empty() && opList.top() != '(') {
        result << opList.top() << ' ';
        opList.pop()
      }
      if (!opList.empty()) {
        result << opList.top();
        opList.pop()
      }
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      while (!opList.empty() && priority(opList.top()) >= priority(ch)) {
        result << opList.top() << ' ';
        opList.pop()
      }
      opList.push(ch);
    }
    index++;
  }

  while (!opList.empty()) {
    result << opList.top() << ' ';
    opList.pop()
  }
  std::string output = result.str();
  if (!output.empty() && output.back() == ' ') {
    output.pop_back();
  }
  return output;
}

int eval(const std::string& pref) {
  std::stack<int> vals;
  std::istringstream iss(pref);
  std::string part;

  while (iss >> part) {
    if (std::isdigit(part[0])) {
      vals.push(std::stoi(part));
    } else {
      int right = vals.top();
      vals.pop()
      int left = vals.top();
      vals.pop()
      switch (part[0]) {
        case '+': vals.push(left + right); break;
        case '-': vals.push(left - right); break;
        case '*': vals.push(left * right); break;
        case '/': vals.push(left / right); break;
      }
    }
  }
  return vals.top();
}
