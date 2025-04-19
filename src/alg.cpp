// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> opStack;
  std::string output;
  for (size_t i = 0; i < inf.length(); ++i) {
    char c = inf[i];
    if (std::isdigit(c)) {
      // читаем полное число
      while (i < inf.length() && std::isdigit(inf[i])) {
        output += inf[i++];
      }
      output += ' ';
      --i;
    } else if (c == '(') {
      opStack.push(c);
    } else if (c == ')') {
      while (!opStack.isEmpty() && opStack.top() != '(') {
        output += opStack.pop();
        output += ' ';
      }
      if (!opStack.isEmpty()) opStack.pop(); // удаляем '('
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!opStack.isEmpty() && priority(opStack.top()) >= priority(c)) {
        output += opStack.pop();
        output += ' ';
      }
      opStack.push(c);
    }
  }

  while (!opStack.isEmpty()) {
    output += opStack.pop();
    output += ' ';
  }

  return output;
}

int eval(const std::string& post) {
  TStack<int, 100> valStack;
  for (size_t i = 0; i < post.length(); ++i) {
    char c = post[i];
    if (std::isdigit(c)) {
      int num = 0;
      while (i < post.length() && std::isdigit(post[i])) {
        num = num * 10 + (post[i++] - '0');
      }
      valStack.push(num);
      --i;
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      int b = valStack.pop();
      int a = valStack.pop();
      switch (c) {
        case '+': valStack.push(a + b); break;
        case '-': valStack.push(a - b); break;
        case '*': valStack.push(a * b); break;
        case '/': valStack.push(a / b); break;
      }
    }
  }
  return valStack.pop();
}
