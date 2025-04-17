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
  TStack<char, 100> SignStack;
  for (int i = 0; i < inf.length(); i++) {
    char temp = inf[i];
    if (isdigit(temp)) {
      std::string temp_number;
      while (i < inf.length() && isdigit(inf[i])) {
        temp_number += inf[i];
        i++;
      }
      i--;
      postfix += temp_number;
      postfix += " ";
    } else if (temp == '(') {
      SignStack.push(temp);
    } else if (temp == ')') {
      while (!SignStack.isempty() && SignStack.top() != '(') {
        postfix += SignStack.top();
        postfix += " ";
        SignStack.pop();
      }
      if (!SignStack.isempty() && SignStack.top() == '(') {
        SignStack.pop();
      }
    } else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
      while (!SignStack.isempty() &&
        checkpriority(temp) <= checkpriority(SignStack.top())) {
        postfix += SignStack.top();
        postfix += " ";
        SignStack.pop();
      }
      SignStack.push(temp);
    } else if (temp == ' ') {
      continue;
    }
  }
  while (!SignStack.isempty()) {
    postfix += SignStack.top();
    postfix += " ";
    SignStack.pop();
  }
  if (!postfix.empty() && postfix.back() == ' ') {
    postfix.pop_back();
  }
  return postfix;
}

int eval(const std::string& pref) {
  TStack<int, 100> NumberStack;
  for (int i = 0; i < pref.length(); i++) {
    char temp = pref[i];
    if (isdigit(temp)) {
      std::string number;
      while (i < pref.length() && isdigit(pref[i])) {
        number += pref[i];
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
