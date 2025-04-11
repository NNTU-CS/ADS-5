// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include <map>
#include "tstack.h"

int getPriorityOp(char op) {
  switch (op) {
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    default: return 0;
  }
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::stringstream result;
  std::string number;
  
  for (char c : inf) {
    if (isdigit(c)) {
      number += c;
    } else {
      if (!number.empty()) {
        result << number << " ";
        number.clear();
      }
      
      if (c == '(') {
        stack.push(c);
      } else if (c == ')') {
        while (!stack.isEmpty() && stack.peek() != '(') {
          result << stack.pop() << " ";
        }
        stack.pop();
      } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        while (!stack.isEmpty() &&
          getPriorityOp(stack.peek()) >= getPriorityOp(c)) {
          result << stack.pop() << " ";
        }
        stack.push(c);
      }
    }
  }
  if (!number.empty()) {
    result << number << " ";
  }
  while (!stack.isEmpty()) {
    result << stack.pop() << " ";
  }
  std::string outputPos = result.str();
  if (!outputPos.empty() && outputPos.back() == ' ') {
    outputPos.pop_back();
  }
  return outputPos;
}

int eval(const std::string& pref) 
TStack<int, 100> stack;
std::stringstream ss(pref);
std::string token;

while (ss >> token) {
  if (isdigit(token[0])) {
    stack.push(std::stoi(token));
  } else {
    int b = stack.pop();
    int a = stack.pop();
    switch (token[0]) 
    case '+': stack.push(a + b); break;
    case '-': stack.push(a - b); break;
    case '*': stack.push(a * b); break;
    case '/': stack.push(a / b); break;
  }
}
}
     return stack.pop();
 }
