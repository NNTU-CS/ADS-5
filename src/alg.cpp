// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string result;
  std::map<char, int> precedence = {
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2}
  };

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    
    if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        result += inf[i++];
      }
      result += ' ';
      i--;
    }
    else if (c == '(') {
      stack.push(c);
    }
    else if (c == ')') {
      while (!stack.isEmpty() && stack.peek() != '(') {
        result += stack.pop();
        result += ' ';
      }
      stack.pop();
    }
    else if (precedence.count(c)) {
      while (!stack.isEmpty() && stack.peek() != '(' && 
             precedence[stack.peek()] >= precedence[c]) {
        result += stack.pop();
        result += ' ';
      }
      stack.push(c);
    }
  }

  while (!stack.isEmpty()) {
    result += stack.pop();
    result += ' ';
  }

  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }

  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::string numStr;

  for (char c : post) {
    if (isdigit(c)) {
      numStr += c;
    }
    else if (c == ' ' && !numStr.empty()) {
      stack.push(std::stoi(numStr));
      numStr.clear();
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/') {
      int right = stack.pop();
      int left = stack.pop();
      
      switch (c) {
        case '+': stack.push(left + right); break;
        case '-': stack.push(left - right); break;
        case '*': stack.push(left * right); break;
        case '/': stack.push(left / right); break;
      }
    }
  }

  return stack.pop();
}
