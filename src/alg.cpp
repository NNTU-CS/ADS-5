// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include "tstack.h"

int priority(char op) {
  switch (op) {
    case '*': case '/': return 3;
    case '+': case '-': return 2;
    default: return 1;
  }
}

bool checkIfOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> operators;
  std::string postfix;

  for (size_t n = 0; n < infix.size(); ++n) {
    char ch = infix[n];

    if (std::isspace(ch)) continue;

    if (std::isdigit(ch)) {
      while (n < infix.size() && std::isdigit(infix[n])) {
        postfix += infix[n++];
      }
      postfix += ' ';
      n--;
    } else if (ch == '(') {
      operators.push(ch);
    } else if (ch == ')') {
      while (operators.hasElements() && operators.check() != '(') {
        postfix += operators.remove();
        postfix += ' ';
      }
      operators.remove(); // Remove '('
    } else if (checkIfOperator(ch)) {
      while (operators.hasElements() &&
             priority(operators.check()) >= priority(ch)) {
        postfix += operators.remove();
        postfix += ' ';
      }
      operators.push(ch);
    }
  }

  while (operators.hasElements()) {
    postfix += operators.remove();
    postfix += ' ';
  }

  if (!postfix.empty() && postfix.back() == ' ') {
    postfix.pop_back();
  }

  return postfix;
}

int eval(const std::string& pref) {
   TStack<int, 100> numbers;
  std::istringstream iss(postfix);
  std::string token;

  while (iss >> token) {
    if (std::isdigit(token[0])) {
      numbers.push(std::stoi(token));
    } else if (checkIfOperator(token[0])) {
      int t = numbers.remove();
      int p = numbers.remove();
      switch (token[0]) {
        case '+': numbers.push(p + t); break;
        case '-': numbers.push(p - t); break;
        case '*': numbers.push(p * t); break;
        case '/': numbers.push(p / t); break;
      }
    }
  }

  return numbers.remove();
}
