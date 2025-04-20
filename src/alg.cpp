// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include <stack>
#include "tstack.h"
int priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;}}

std::string infx2pstfx(const std::string& inf) {
  std::string postfix = "";
  TStack<char, 100> stack;

  for (char ln: inf) {
       ln = inf[i];
        if (isspace(ln)) continue;
        if (isalnum(ln)) {
          std::string num;
          num += ln;
          size_t pos = i + 1;
          while (pos < inf.length() && isdigit(inf[pos])) {
              num += inf[pos];
              pos++;
              i++;
  }
  postfix += num + " ";
} else if (ln == '(') {
      stack.push(ln);}
} else if (ln == ')') {
      while (!stack.isEmpty() && stack.peek() != '(') {
          postfix += stack.pop();
          postfix += " ";
      }
      if (!stack.isEmpty() && stack.peek() == '(') {
          stack.pop();
} else {
         while (!stack.isEmpty() && priority(ln) <= priority(stack.peek())) {
            postfix += stack.pop();
            postfix += " ";
        }
        stack.push(ln);
      }
  }
  while (!stack.isEmpty()) {
          postfix += stack.pop();
          postfix += " ";
      }

  if (!postfix.empty() && postfix.back() == ' ') {
      postfix.pop_back();
  }

  return postfix;

int eval(const std::string& pref) {
  TStack<int, 100> stack;
  std::string num;
  for (char ln : post) {
      if (isdigit(ln)) {
          num += ln;
      } else if (isspace(ln)) {
           if (num.empty()) continue;
            stack.push(std::stoi(num));
            num = "";
        } else if (ln == '+' || ln == '-' || ln == '*' || ln == '/') {
            int operand2 = stack.pop();
            int operand1 = stack.pop();
            int result;}
        switch (c) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                default: return 0;
            }
            stack.push(result);
  }
  }
    if (!stack.isEmpty()) {
            return stack.pop();
        } else {
            return 0;
        }
}
