// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>
#include <vector>
#include <map>

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}
std::string infx2pstfx(const std::string& inf) {
  std::stack<char> operators;
  std::ostringstream output;
  std::istringstream tokens(inf);
  std::string token;
  while (tokens >> token) {
    if (std::isdigit(token[0])) {
      output << token << ' ';
    }
    else if (token.size() == 1 && strchr("+-*/", token[0])) {
      while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
        output << operators.top() << ' ';
        operators.pop();
      }
      operators.push(token[0]);
    } 
    else if (token == "(") {
      operators.push('(');
    }
    else if (token == ")") {
      while (!operators.empty() && operators.top() != '(') {
        output << operators.top() << ' ';
        operators.pop();
      }
      operators.pop();
    }
  }
  while (!operators.empty()) {
    output << operators.top() << ' ';
    operators.pop();
  }
  return output.str();
}

int eval(const std::string& post) {
  std::stack<int> operands;
  std::istringstream tokens(post);
  std::string token;
  while (tokens >> token) {
    if (std::isdigit(token[0])) {
      operands.push(std::stoi(token));
    }
    else if (token.size() == 1 && strchr("+-*/", token[0])) {
      int right = operands.top(); operands.pop();
      int left = operands.top(); operands.pop();
      int result;
      switch (token[0]) {
        case '+': result = left + right; break;
        case '-': result = left - right; break;
        case '*': result = left * right; break;
        case '/': result = left / right; break;
      }
      operands.push(result);
    }
  }
  return operands.top();
}
