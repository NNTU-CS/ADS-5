// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include <sstream>
#include <map>
#include "tstack.h"
int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}
std::string infx2pstfx(const std::string& inf) {
  std::ostringstream output;
  TStack<char, 100> opStack;
  int i = 0;
  while (i < inf.size()) {
    if (isspace(inf[i])) {
      i++;
    } else if (isdigit(inf[i])) {
      while (i < inf.size() && isdigit(inf[i])) {
        output << inf[i++];
      }
      output << ' ';
    } else if (inf[i] == '(') {
      opStack.push(inf[i++]);
    } else if (inf[i] == ')') {
      while (!opStack.isEmpty() && opStack.peek() != '(') {
        output << opStack.pop() << ' ';
      }
      opStack.pop(); // удаляем '('
      i++;
    } else if (isOperator(inf[i])) {
      while (!opStack.isEmpty() && \
        precedence(opStack.peek()) >= precedence(inf[i])) {
        output << opStack.pop() << ' ';
      }
      opStack.push(inf[i++]);
    } else {
        i++;  // пропустить неизвестный символ
    }
  }

  while (!opStack.isEmpty()) {
    output << opStack.pop() << ' ';
  }

  return output.str();
}

int eval(const std::string& pref) {
  std::istringstream input(pref);
  TStack<int, 100> valStack;
  std::string token;

  while (input >> token) {
    if (isdigit(token[0])) {
      valStack.push(std::stoi(token));
    } else {
      int b = valStack.pop();
      int a = valStack.pop();
      if (token == "+") valStack.push(a + b);
      else if (token == "-") valStack.push(a - b);
      else if (token == "*") valStack.push(a * b);
      else if (token == "/") valStack.push(a / b);
    }
  }

  return valStack.pop();
}
