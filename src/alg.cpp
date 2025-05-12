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
      stack.push(c);
      i++;
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.pop();
      i++;
    } else {
      while (!stack.isEmpty() && precedence(c) <= precedence(stack.top())) {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.push(c);
      i++;
    }
  }
  while (!stack.isEmpty()) {
    postfix += stack.pop();
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
      stack.push(stoi(token));
    } else {
      int b = stack.pop();
      int a = stack.pop();
      switch (token[0]) {
        case '+': stack.push(a + b); break;
        case '-': stack.push(a - b); break;
        case '*': stack.push(a * b); break;
        case '/': stack.push(a / b); break;
      }
    }
  }
  return stack.pop();
}

