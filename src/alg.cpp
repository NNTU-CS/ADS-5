// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool is_operator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}
int prioty(char op) {
  if (op == '+' || op == '-')
      return 1;
  if (op == '*' || op == '/')
      return 2;
  return 0;  
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string output = "";
  std::string number = "";
  for (size_t i = 0; i < inf.length(); i++) {
      char c = inf[i];
      if (isdigit(c)) {
          number += c;
          continue;
      } else if (!number.empty()) {
          output += number + " ";
          number = "";
      }
      if (c == '(') {
          stack.push(c);
      }
      else if (c == ')') {
          while (!stack.is_empty() && stack.peek() != '(') {
              output += stack.peek();
              output += " ";
              stack.pop();
          }
          if (!stack.is_empty()) {
              stack.pop();  
          }
      }
      else if (is_operator(c)) {
          while (!stack.is_empty() && stack.peek() != '(' && 
                prioty(stack.peek()) >= prioty(c)) {
              output += stack.peek();
              output += " ";
              stack.pop();
          }
          stack.push(c);
      }
  }
  if (!number.empty()) {
      output += number + " ";
  }
  while (!stack.is_empty()) {
      if (stack.peek() != '(') {
          output += stack.peek();
          output += " ";
      }
      stack.pop();
  }
  return output;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack2;
  std::string number = "";
  for (size_t i = 0; i < pref.length(); i++) {
    char c = pref[i];
    if (isdigit(c)) {
      number += c;
    }
    else if (c == ' ') {
      if (!number.empty()) {
        stack2.push(std::stoi(number));
        number = "";
      }
    }
    else if (is_operator(c)) {
      if (!stack2.is_empty()) {
        int b = stack2.peek();
        stack2.pop();
        
        if (!stack2.is_empty()) {
          int a = stack2.peek();
          stack2.pop();
          
          if (c == '+') stack2.push(a + b);
          else if (c == '-') stack2.push(a - b);
          else if (c == '*') stack2.push(a * b);
          else if (c == '/') stack2.push(a / b);
        }
      }
    }
  }
  
  if (!number.empty()) {
    stack2.push(std::stoi(number));
  }
  
  return stack2.peek();
  return 0;
}
