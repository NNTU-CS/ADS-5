// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string postfix;
  std::map<char, int> precedence = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
  };

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    
    if (c == ' ') {
      continue;
    } else if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        postfix += inf[i++];
      }
      postfix += ' ';
      i--;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.pop();
    } else {
      while (!stack.isEmpty() && stack.top() != '(' && 
           precedence[stack.top()] >= precedence[c]) {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.push(c);
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

int eval(const std::string& post) {
  TStack<int, 100> stack;
  
  for (size_t i = 0; i < post.size(); ++i) {
    char c = post[i];
    
    if (c == ' ') {
      continue;
    } else if (isdigit(c)) {
      int num = 0;
      while (i < post.size() && isdigit(post[i])) {
        num = num * 10 + (post[i] - '0');
        i++;
      }
      stack.push(num);
      i--;
    } else {
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
