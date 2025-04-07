// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include "tstack.h"

int getPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  std::string output;
  TStack<char, 100> opStack;

  for (size_t i = 0; i < inf.length(); i++) {
    char ch = inf[i];
    if (ch == ' ') continue;

    if (isdigit(ch)) {
      while (i < inf.length() && isdigit(inf[i])) {
        output.push_back(inf[i]);
        i++;
      }
      i--;
      output.push_back(' ');
    } else if (ch == '(') {
      opStack.Push(ch);
    } else if (ch == ')') {
      while (!opStack.IsEmpty() && opStack.Top() != '(') {
        output.push_back(opStack.Top());
        output.push_back(' ');
        opStack.Pop();
      }
      opStack.Pop();
    } else {
      while (!opStack.IsEmpty() && 
             getPriority(opStack.Top()) >= getPriority(ch)) {
        output.push_back(opStack.Top());
        output.push_back(' ');
        opStack.Pop();
      }
      opStack.Push(ch);
    }
  }

  while (!opStack.IsEmpty()) {
    output.push_back(opStack.Top());
    output.push_back(' ');
    opStack.Pop();
  }

  if (!output.empty() && output.back() == ' ') {
    output.pop_back();
  }

  return output;
}

int eval(const std::string& post) {
  TStack<int, 100> numStack;
  std::istringstream iss(post);
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0])) {
      numStack.Push(stoi(token));
    } else {
      int b = numStack.Top();
      numStack.Pop();
      int a = numStack.Top();
      numStack.Pop();

      if (token == "+") numStack.Push(a + b);
      else if (token == "-") numStack.Push(a - b);
      else if (token == "*") numStack.Push(a * b);
      else if (token == "/") numStack.Push(a / b);
    }
  }

  return numStack.Top();
}
