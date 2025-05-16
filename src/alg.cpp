// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::map<char, int> priority {
{'(', 0}, {')', 1}, {'-', 2}, {'+', 2}, {'/', 3}, {'*', 3}
};

std::string infx2pstfx(const std::string& inf) {
  std::string str = "";
  std::stack<char> stack1;
  for (int i = 0; i < inf.length(); i++) {
    if (isdigit(inf[i])) {
      str += inf[i];
      str += ' ';
    } else {
      if (inf[i] == '(') {
        stack1.push('(');
      } else if (inf[i] == ')') {
        while (!stack1.empty() && stack1.top() != '(') {
          str += stack1.top(); stack1.pop();
          str += ' ';
        }
        if (!stack1.empty() && stack1.top() == '(') {
          stack1.pop();
        }
      } else {
        while (!stack1.empty() && priority[inf[i]] <= priority[stack1.top()]) {
          str += stack1.top(); stack1.pop();
          str += ' ';
        }
        stack1.push(inf[i]);
      }
    }
  }
  while (!stack1.empty()) {
    str += stack1.top(); stack1.pop();
    str += ' ';
  }

  return str;
}

int eval(const std::string& pref) {
  std::stack<int> stack2;
  std::string num;
  for (char i : pref) {
    if (isdigit(i)) {
       num += i;
       } else if (i == ' ' && !num.empty()) {
      stack2.push(std::stoi(num));
      num.clear();
       } else if (i == '+" || i == '-' || i == '*' || i == '-') {
      int b = stack2.top(); stack2.pop();
      int a = stack2.top(); stack2.pop();
      switch (i) {
        case '+': stack2.push(a + b); break;
        case '-': stack2.push(a - b); break;
        case '*': stack2.push(a * b); break;
        case '/': stack2.push(a / b); break;
      }
  }
}
  return stack2.top();
}
