// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include "tstack.h"

int getOperatorPriority(char op) {
  switch (op) {
    case '*': case '/': return 3;
    case '+': case '-': return 2;
    default: return 1;
  }
}

bool isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

std::string infToPref(const std::string& inf) {
  TStack<char, 100> operatorStack;
  std::string pref;

  for (size_t idx = 0; idx < inf.size(); ++idx) {
    char currentChar = inf[idx];

    if (std::isspace(currentChar)) continue;

    if (std::isdigit(currentChar)) {
      while (idx < inf.size() && std::isdigit(inf[idx])) {
        pref += inf[idx++];
      }
      pref += ' ';
      idx--;
    } else if (currentChar == '(') {
      operatorStack.push(currentChar);
    } else if (currentChar == ')') {
      while (operatorStack.hasElements() && operatorStack.check() != '(') {
        pref += operatorStack.remove();
        pref += ' ';
      }
      operatorStack.remove();
    } else if (isOperator(currentChar)) {
      while (operatorStack.hasElements() &&
             getOperatorPriority(operatorStack.check()) >= getOperatorPriority(currentChar)) {
        pref += operatorStack.remove();
        pref += ' ';
      }
      operatorStack.push(currentChar);
    }
  }

  while (operatorStack.hasElements()) {
    pref += operatorStack.remove();
    pref += ' ';
  }

  if (!pref.empty() && pref.back() == ' ') {
    pref.pop_back();
  }

  return pref;
}

int evaluatePref(const std::string& pref) {
  TStack<int, 100> numberStack;
  std::istringstream inputStream(pref);
  std::string token;

  while (inputStream >> token) {
    if (std::isdigit(token[0])) {
      numberStack.push(std::stoi(token));
    } else if (isOperator(token[0])) {
      int secondOperand = numberStack.remove();
      int firstOperand = numberStack.remove();
      switch (token[0]) {
        case '+': numberStack.push(firstOperand + secondOperand); break;
        case '-': numberStack.push(firstOperand - secondOperand); break;
        case '*': numberStack.push(firstOperand * secondOperand); break;
        case '/': numberStack.push(firstOperand / secondOperand); break;
      }
    }
  }

  return numberStack.remove();
}
