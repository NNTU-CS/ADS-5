// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

using std::string;
using std::stringstream;
using std::isdigit;

static int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

string infx2pstfx(const string& inf) {
  TStack<char, 100> stack;
  string postfix;
  for (size_t i = 0; i < inf.size();) {
    char c = inf[i];
    if (isdigit(c)) {
      string num;
      while (i < inf.size() && isdigit(inf[i])) {
        num += inf[i];
        i++;
      }
      postfix += num + " ";
    } else if (c == '(') {
      stack.Push(c);
      i++;
    } else if (c == ')') {
      while (!stack.IsEmpty() && stack.Top() != '(') {
        postfix += stack.Pop();
        postfix += ' ';
      }
      stack.Pop();
      i++;
    } else {
      while (!stack.IsEmpty() && precedence(c) <= precedence(stack.Top())) {
        postfix += stack.Pop();
        postfix += ' ';
      }
      stack.Push(c);
      i++;
    }
  }
  while (!stack.IsEmpty()) {
    postfix += stack.Pop();
    postfix += ' ';
  }
  if (!postfix.empty() && postfix.back() == ' ') {
     postfix.pop_back();
  }
  return postfix;
}

int eval(const string& post) {
  TStack<int, 100> stack;
  stringstream ss(post);
  string token;
  while (ss >> token) {
    if (isdigit(token[0])) {
      stack.Push(stoi(token));
    } else {
      int b = stack.Pop();
      int a = stack.Pop();
      switch (token[0]) {
        case '+': stack.Push(a + b); break;
        case '-': stack.Push(a - b); break;
        case '*': stack.Push(a * b); break;
        case '/': stack.Push(a / b); break;
      }
    }
  }
  return stack.Pop();
}
