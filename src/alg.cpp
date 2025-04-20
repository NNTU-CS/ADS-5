// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int operationPriority(char operation) {
  switch (operation) {
    case('('): return 0;
    case(')'): return 1;
    case('-'): return 2;
    case('+'): return 2;
    case('*'): return 3;
    case('/'): return 3;
    default: return -1;
  }
}

std::string infx2pstfx(const std::string& inf){
  std::string postfixStr = "";
  TStack<char, 100> signStack;
  for (int i = 0; i < inf.length(); i++) {
    char temp = inf[i];
    if (isdigit(temp)){
      std::string temp_num;
      while (i < inf.length() && isdigit(inf[i])) {
        temp_num += inf[i];
        i++;
      }
      i--;
      postfixStr += temp_num;
      postfixStr += " ";
    } else if (temp == '(') {
      signStack.push(temp);
    } else if (temp == ')') {
      while (!signStack.isempty() && signStack.top() != '(') {
        postfixStr += signStack.top();
        postfixStr += " ";
        signStack.pop();
      }
      if (!signStack.isempty() && signStack.top() == '(') {
        signStack.pop();
      }
    } else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
      while (sSignStack.isempty() &&
        operationPriority(temp) <= operationPriority(signStack.top())) {
        postfixStr += signStack.top();
        postfixStr += " ";
        signStack.pop();
      }
      signStack.push(temp);
    } else if (temp == ' ') {
      continue;
    }
  }
  while (!signStack.isempty()) {
    postfixStr += signStack.top();
    postfixStr += " "
    signStack.pop();
  }
  if (!postfixStr.empty() && postfixStr.back() == ' ') {
    postfixStr.pop_back();
  }
  return postfixStr;
}

int eval(const std::string& pref) {
  TStack<int, 100> StackNum;
  for (int i = 0; i < pref.length(); i++) {
    char temp = pref[i];
    if (isdigit(temp)) {
      std::string number;
      while (i < pref.length() && isdigit(pref[i])) {
        number += pref[i];
        i++;
      }
      i--;
      StackNum.push(std::stoi(number));
    } else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
      int right = StackNum.top();
      StackNum.pop();
      int left = StackNum.top();
      StackNum.pop();
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
      StackNum.push(result);
    }
  }
  return StackNum.top();
}
