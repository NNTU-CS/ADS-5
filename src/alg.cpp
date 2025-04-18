#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

#include "tstack.h"

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

bool isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

std::string infx2pstfx(const std::string& inf) {
  std::ostringstream output;
  TStack<char, 100> stack;

  for (size_t i = 0; i < inf.length(); ++i) {
    if (std::isdigit(inf[i])) {
      while (i < inf.length() && std::isdigit(inf[i])) {
        output << inf[i++];
      }
      output << ' ';
      --i;
    } else if (inf[i] == '(') {
      stack.push(inf[i]);
    } else if (inf[i] == ')') {
      while (!stack.isEmpty() && stack.peek() != '(') {
        output << stack.pop() << ' ';
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (isOperator(inf[i])) {
      while (!stack.isEmpty() &&
             precedence(stack.peek()) >= precedence(inf[i])) {
        output << stack.pop() << ' ';
      }
      stack.push(inf[i]);
    }
  }

  while (!stack.isEmpty()) {
    output << stack.pop() << ' ';
  }

  return output.str();
}

int applyOp(int a, int b, char op) {
  switch (op) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      if (b == 0) throw std::runtime_error("Division by zero");
      return a / b;
  }
  throw std::runtime_error("Unknown operator");
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream input(post);
  std::string token;

  while (input >> token) {
    if (std::isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else if (token.length() == 1 && isOperator(token[0])) {
      int b = stack.pop();
      int a = stack.pop();
      int res = applyOp(a, b, token[0]);
      stack.push(res);
    }
  }

  return stack.pop();
}
