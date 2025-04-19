// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include "tstack.h"

int priority(char symbol) {
  if (symbol == '*' || symbol == '/') return 3;
  if (symbol == '+' || symbol == '-') return 2;
  return 1;
}

bool checkIfOperator(char symbol) {
  return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

std::string infx2pstfx(const std::string& expression) {
  TStack<char, 100> op_stack;
  std::string result;

  for (size_t pos = 0; pos < expression.length(); ++pos) {
    char current = expression[pos];

    if (std::isspace(current)) continue;

    if (std::isdigit(current)) {
      while (pos < expression.length() && std::isdigit(expression[pos])) {
        result += expression[pos++];
      }
      result += ' ';
      pos--;
    } else if (current == '(') {
      op_stack.push(current);
    } else if (current == ')') {
      while (op_stack.hasElements() && op_stack.check() != '(') {
        result += op_stack.remove();
        result += ' ';
      }
      if (op_stack.hasElements()) op_stack.remove();
    } else if (checkIfOperator(current)) {
      while (op_stack.hasElements()
        && priority(op_stack.check()) >= priority(current)) {
        result += op_stack.remove();
        result += ' ';
      }
      op_stack.push(current);
    }
  }

  while (op_stack.hasElements()) {
    result += op_stack.remove();
    result += ' ';
  }

  if (!result.empty() && result[result.length()-1] == ' ')
    result.erase(result.length()-1);

  return result;
}

int eval(const std::string& postfix) {
  TStack<int, 100> num_stack;
  std::istringstream stream(postfix);
  std::string part;

  while (stream >> part) {
    if (std::isdigit(part[0])) {
      num_stack.push(std::stoi(part));
    } else if (checkIfOperator(part[0]) && part.size() == 1) {
      int right = num_stack.remove();
      int left = num_stack.remove();
      switch (part[0]) {
        case '+': num_stack.push(left + right); break;
        case '-': num_stack.push(left - right); break;
        case '*': num_stack.push(left * right); break;
        case '/': num_stack.push(left / right); break;
      }
    }
  }

  return num_stack.remove();
}
