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
  TStack<char, 100> operators;
  std::ostringstream result;

  size_t idx = 0;
  while (idx < inf.size()) {
    char symbol = inf[idx];

    if (std::isdigit(symbol)) {
      while (idx < inf.size() && std::isdigit(inf[idx])) {
        result << inf[idx++];
      }
      result << ' ';
      --idx;
    } else if (symbol == '(') {
      operators.add(symbol);
    } else if (symbol == ')') {
      while (!operators.isVoid() && operators.getTop() != '(') {
        result << operators.remove() << ' ';
      }
      if (!operators.isVoid()) {
        operators.remove(); // Убираем '('
      }
    } else if (symbol == '+' || symbol == '-' ||
               symbol == '*' || symbol == '/') {
      while (!operators.isVoid() &&
             priority(operators.getTop()) >= priority(symbol)) {
        result << operators.remove() << ' ';
      }
      operators.add(symbol);
    }
    ++idx;
  }

  while (!operators.isVoid()) {
    result << operators.remove() << ' ';
  }

  std::string output = result.str();
  if (!output.empty() && output.back() == ' ')
    output.pop_back();

  return output;
}

int eval(const std::string& post) {
  TStack<int, 100> values;
  std::istringstream iss(post);
  std::string part;

  while (iss >> part) {
    if (std::isdigit(part[0])) {
      values.add(std::stoi(part));
    } else {
      int rhs = values.remove();
      int lhs = values.remove();
      switch (part[0]) {
        case '+': values.add(lhs + rhs); break;
        case '-': values.add(lhs - rhs); break;
        case '*': values.add(lhs * rhs); break;
        case '/': values.add(lhs / rhs); break;
      }
    }
  }

  return values.remove();
}
