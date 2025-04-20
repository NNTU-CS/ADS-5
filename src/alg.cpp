// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  std::string postfix;
  TStack<char, 100> opStack;
  for (int i = 0; i < inf.length(); i++) {
    char temp = inf[i];
    if (isdigit(temp)) {
      std::string temp_string;
      while (i < inf.length() && isdigit(inf[i])) {
        temp_string += temp;
        i++;
        temp = inf[i];
      }
      i--;
      postfix += temp_string;
      postfix += " ";
    } else if (temp == '(') {
      opStack.push(temp);
    } else if (temp == ')') {
      while (!opStack.isEmpty() && opStack.get() != '(') {
        postfix += opStack.get();
        postfix += " ";
        opStack.pop();
      }
      if (!opStack.isEmpty() && opStack.get() == '(') {
        opStack.pop();
      }
    } else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
      while (!opStack.isEmpty() && checkpriority(temp) <=
        checkpriority(opStack.get())) {
        postfix += opStack.get();
        postfix += " ";
        opStack.pop();
      }
      opStack.push(temp);
    } else if (temp == ' '){
      continue;
    }
  }
  while (!opStack.isEmpty()) {
    postfix += opStack.get();
    postfix += " ";
    opStack.pop();
  }
  if (!postfix.empty() && postfix.back() == ' ') {
    postfix.pop_back();
  }
  return postfix;
}

int eval(const std::string& pref) {
  // добавьте код
  return 0;
}
