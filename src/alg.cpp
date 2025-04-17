// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isDigit(char ch) {
  return ch >= '0' && ch <= '9';
}

bool isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int toInt(const std::string& s) {
  int result = 0;
  for (size_t i = 0; i < s.length(); ++i) {
    result = result * 10 + (s[i] - '0');
  }
  return result;
}

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
      while (i < inf.length() && isDigit(inf[i])) {
        output += inf[i++];
      }
      output += ' ';
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
      while (!stack.isEmpty() && stack.peek() != '(' && precedence[ch] <= precedence[stack.peek()]) {
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
      int b = stack.pop();
      int a = stack.pop();
      switch (ch) {
        case '+': stack.push(a + b); break;
        case '-': stack.push(a - b); break;
        case '*': stack.push(a * b); break;
        case '/':
          if (b == 0) throw "Division by zero";
          stack.push(a / b);
          break;
      }
    }
  }
  return stack.pop();
}
