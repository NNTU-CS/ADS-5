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
            return 0;}

std::string infx2pstfx(const std::string& inf) {
  std::string postfix = "";
  TStack<char, 100> stack1;

    for (int i = 0; i < inf.length(); ++i) {
        char ln = inf[i]; 
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
  }
    }     
  postfix += num + " ";
} else if (ln == '(') {
      stack1.Push(ln);
        } else if (ln == ')') {
      while (!stack1.IsEmpty() && stack1.peek() != '(') {
          postfix += stack1.Pop();
          postfix += " ";
      }
      if (!stack1.IsEmpty() && stack1.peek() == '(') {
          stack1.Pop();
} else {
         while (!stack1.IsEmpty() && priority(ln) <= priority(stack1.peek())) {
            postfix += stack1.Pop();
            postfix += " ";
        }
        stack1.Push(ln);
      }
  }
  while (!stack1.IsEmpty()) {
          postfix += stack1.Pop();
          postfix += " ";
      }

  if (!postfix.empty() && postfix.back() == ' ') {
      postfix.pop_back();
  }

  return postfix;
}


int eval(const std::string& pref) {
  TStack<int, 100> stack2;
  std::string num;
  for (char ln : post) {
      if (isdigit(ln)) {
          num += ln;
      } else if (isspace(ln)) {
          if (num.empty()) continue;
          stack2.Push(std::stoi(num));
          num = "";
        } else if (ln == '+' || ln == '-' || ln == '*' || ln == '/') {
            int operand2 = stack2.Pop();
            int operand1 = stack2.Pop();
            int result;}
        switch (c) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                default: return 0;
            }
            stack2.Push(result);
  }
  }
    if (!stack1.IsEmpty()) {
            return stack2.Pop();
        } else {
            return 0;
        }
}
