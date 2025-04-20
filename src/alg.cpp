// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int PriorityOperation(char operation) {
  switch (operation) {
    case('('): return 0;
    case(')'): return 1;
    case('-'): return 2;
    case('+'): return 2;
    case('/'): return 3;
    case('*'): return 3;
    default: return -1;
  }
}

std::string infx2pstfx(const std::string& inf) {
  std::string postfixStr = "";
  TStack<char, 100> SignStack;
  for (int i = 0; i < inf.length(); i++) {
    char temp = inf[i];
    if (isdigit(temp)) {
      std::string temp_num;
      while (i < inf.length() && isdigit(inf[i])) {
        temp_num += inf[i];
        i++;
      }
      i--;
      postfixStr += temp_num;
      postfixStr += " ";
    } else if (temp == '(') {
      SignStack.push(temp);
    } else if (temp == ')') {
      while (!SignStack.isempty() && SignStack.top() != '(') {
        postfixStr += SignStack.top();
        postfixStr += " ";
        SignStack.pop();
      }
      if (!SignStack.isempty() && SignStack.top() == '(') {
        SignStack.pop();
      }
    } else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
      while (!SignStack.isempty() &&
        PriorityOperation(temp) <= PriorityOperation(SignStack.top())) {
        postfixStr += SignStack.top();
        postfixStr += " ";
        SignStack.pop();
      }
      SignStack.push(temp);
    } else if (temp == ' ') {
      continue;
    }
  }
  while (!SignStack.isempty()) {
    postfixStr += SignStack.top();
    postfixStr += " ";
    SignStack.pop();
  }
  if (!postfixStr.empty() && postfixStr.back() == ' ') {
    postfixStr.pop_back();
  }
  return postfixStr;
}

int eval(const std::string& pref) {
  TStack<int, 100> NumberStack;
  for (int i = 0; i < pref.length(); i++) {
    char temp = pref[i];
    if (isdigit(temp)) {
      std::string num;
      while (i < pref.length() && isdigit(pref[i])) {
        num += pref[i];
        i++;
      }
      i--;
      NumberStack.push(std::stoi(num));
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
