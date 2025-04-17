// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

bool operacia(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int prioritet(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100>stack;
  std::string postfix;

  for (size_t i = 0; i < inf.length(); i++) {
    if (isspace(inf[i])) continue;

    if (isdigit(inf[i])) {
      postfix += inf[i];
      postfix += ' ';
    } else if (inf[i] == '(') {
      stack.push(inf[i]);
    } else if (inf[i] == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        postfix += stack.pop();
        postfix += ' ';
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (operacia(inf[i])) {
      while (!stack.isEmpty() && prioritet(stack.top()) >= prioritet(inf[i])) {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.push(inf[i]);
    }
  }

  while (!stack.isEmpty()) {
    postfix += stack.pop();
    postfix += ' ';
  }

  if (!postfix.empty() && postfix.back() == ' ')
    postfix.pop_back();

  return postfix;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;

  for (size_t i = 0; i < post.length(); i++) {
    if (isspace(post[i])) continue;

    if (isdigit(post[i])) {
      stack.push(post[i] - '0');
    } else if (operacia(post[i])) {
      int a = stack.pop();
      int b = stack.pop();
      stack.push(primer(a, b, post[i]));
    }
  }
  return stack.pop();
}

int primer(int a, int b, char op) {
  switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
  }
  return 0;
}
