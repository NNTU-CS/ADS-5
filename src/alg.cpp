// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int checkpriority(char sign) {
  switch (sign) {
    case('('): return 0;
    case(')'): return 1;
    case('+'): return 2;
    case('-'): return 2;
    case('*'): return 3;
    case('/'): return 3;
    default: return -1;
  }
}

std::string infx2pstfx(const std::string& inf) {
  std::string postfix = "";
  Tstack<char, 100> SignStack;
  for (int i = 0; i < inf.length(); i++) {
    char temp = inf[i];
    if (isdigit(temp)) {
      std::string temp_number;
      while (i < inf.length() && isdigit(inf[i])) {
        temp_number += inf[i];
        i++;
      }
      i--;
      postfix += temp_number + " ";
    } else if (temp == '(') {
      SignStack.push(temp);
    } else if (temp == ')') {
      while (!SignStack.isempty() && !SignStack.top() == '(') {
        postfix += SignStack.top() + " ";
        SignStack.pop();
      }
      if (!SignStack.isempty() && SignStack.top() == '(') {
        SignStack.pop();
      }
    } else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
      while (!SignStack.isempty() &&
        checkpriority(temp) <= checkpriority(SignStack.top())) {
        postfix += SignStack.top() + " ";
        SignStack.pop();
      }
      SignStack.push(temp);
    } else if (temp == ' ') {
      continue;
    }
  }
  while (!SignStack.isempty()) {
    postfix += SignStack.top() + " ";
    SignStack.pop();
  }
  if (!postfix.empty() && postfix.back() == ' ') {
    postfix.pop_back();
  }
  return postfix;
}

int eval(const std::string& pref) {
  Tstack<int, 100> NumberStack;
  for (int i = 0; i < post.length(); i++) {
    char temp = post[i];
    if (isdigit(temp)) {
      std::string number;
      while (i < post.length() && isdigit(post[i])) {
        number += post[i];
        i++;
      }
      i--;
      NumberStack.push(std::stoi(number));
    } else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
      int right = NumberStack.top();
      NumberStack.pop();
      int left = NumberStack.top();
      NumberStack.pop();
      int result;
      switch (temp) {
      case '+':
        result = left + right;
        break;
      case '-':
        result = left - right;
        break;
      case '*':
        result = left * right;
        break;
      case '/':
        result = left / right;
        break;
      }
      NumberStack.push(result);
    }
  }
  return NumberStack.top();
}
