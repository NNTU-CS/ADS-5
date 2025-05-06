// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  std::map<char, int> precedence;
  precedence['+'] = precedence['-'] = 1;
  precedence['*'] = precedence['/'] = 2;
  TStack<char, 100> stack;
  std::string output;
  for (size_t i = 0; i < inf.length(); ++i) {
    char ch = inf[i];
    if (ch == ' ') continue;
    if (isDigit(ch)) {
      std::string num;
      while (i < inf.length() && isDigit(inf[i])) {
        num += inf[i++];
      }
      output += num + ' ';
      --i;
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.isEmpty() && stack.peek() != '(') {
        output += stack.pop();
        output += ' ';
      }
      if (!stack.isEmpty()) stack.pop();
      } else if (isOperator(ch)) {
      while (!stack.isEmpty() && stack.peek() != '(' &&
        precedence[ch] <= precedence[stack.peek()]) {
        output += stack.pop();
        output += ' ';
      }
      stack.push(ch);
    }
  }
  while (!stack.isEmpty()) {
    output += stack.pop();
    output += ' ';
  }
  if (!output.empty() && output.back() == ' ') {
    output.erase(output.size() - 1);
  }
  return output;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack;
  std::string num;
  for (size_t i = 0; i < pref.length(); ++i) {
    char ch = pref[i];
    if (ch == ' ') {
      if (!num.empty()) {
        stack.push(toInt(num));
        num.clear();
      }
    } else if (isDigit(ch)) {
      num += ch;
    } else if (isOperator(ch)) {
      if (stack.isEmpty()) throw "Invalid postfix expression";
      int b = stack.pop();
      if (stack.isEmpty()) throw "Invalid postfix expression";
      int a = stack.pop();
      switch (ch) {
        case '+':
          stack.push(a + b);
          break;
        case '-':
          stack.push(a - b);
          break;
        case '*':
          stack.push(a * b);
          break;
        case '/':
          if (b == 0) throw "Division by zero";
          stack.push(a / b);
          break;
      }
    }
  }
  if (stack.isEmpty()) throw "Invalid postfix expression";
  int result = stack.pop();
  if (!stack.isEmpty()) {
    throw "Invalid postfix expression";
  }
  return result;
}
