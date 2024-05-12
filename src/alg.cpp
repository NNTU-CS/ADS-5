// Copyright 2021 NNTU-CS
#include <string>
#include <stack>
#include <algorithm>
#include "tstack.h"

bool isOperator(char ch) {
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
    return true;
  return false;
}
int precedence(char ch) {
  if (ch == '*' || ch == '/')
    return 2;
  if (ch == '+' || ch == '-')
    return 1;
  return 0;
}
std::string infx2pstfx(std::string inf) {
  std::stack<char> stk;
  std::string prefix;
  for (int i = 0; i < inf.size(); i++) {
    if (isOperator(inf[i])) {
      prefix.push_back(' ');
      while (!stk.empty() && precedence(stk.top()) >= precedence(inf[i])) {
        prefix += stk.top();
        stk.pop();
        prefix.push_back(' ');
      }
      stk.push(inf[i]);
    } else if (inf[i] == '(') {
      stk.push(inf[i]);
    } else if (inf[i] == ')') {
      while (!stk.empty() && stk.top() != '(') {
        prefix.push_back(' ');
        prefix += stk.top();
        stk.pop();
      }
      stk.pop();
    } else {
      prefix += inf[i];
    }
  }
  while (!stk.empty()) {
    prefix.push_back(' ');
    prefix += stk.top();
    stk.pop();
  }
  return prefix;
}
std::string eva(char op, int operand1, int operand2) {
  switch (op) {
    case '+': return std::to_string(operand1 + operand2);
    case '-': return std::to_string(operand1 - operand2);
    case '*': return std::to_string(operand1 * operand2);
    case '/': return std::to_string(operand1 / operand2);
  }
  return 0;
}
int eval(std::string pref) {
  std::stack<std::string> stk;
  std::string pust = " ";
  std::string opera_2;
  std::string opera_1;
  for (int i = 0; i < pref.size(); i++) {
    if (isOperator(pref[i])) {
      if (stk.top() == " ") {
        stk.pop();
      }
      if (stk.top() == "0") {
        while (!stk.empty() && stk.top() != pust) {
          opera_2 += stk.top();
          stk.pop();
        }
        if (opera_2[0] == '0')
          std::reverse(opera_2.begin(), opera_2.end());
      } else {
        while (!stk.empty() && stk.top() != pust) {
          opera_2 += stk.top();
          stk.pop();
          if (opera_2[0] == '0')
            std::reverse(opera_2.begin(), opera_2.end());
        }
        if (stk.top() == " ") {
          stk.pop();
          if (stk.top() == "0") {
            while (!stk.empty() && stk.top() != pust) {
              opera_1 += stk.top();
              stk.pop();
            }
            if (opera_1[0] == '0')
              std::reverse(opera_1.begin(), opera_1.end());
          } else {
            while (!stk.empty() && stk.top() != pust) {
              opera_1 += stk.top();
              stk.pop();
              if (opera_1[0] == '0')
                std::reverse(opera_1.begin(), opera_1.end());
            }
          }
        }
        std::string res = eva(pref[i], std::stoi(opera_1), std::stoi(opera_2));
        stk.push(res);
      }
    } else {
      if (pref[i] == ' ')
        stk.push(" ");
      else
        stk.push(std::to_string(pref[i] - '0'));
    }
    opera_1 = " ";
    opera_2 = " ";
  }
  return std::stoi(stk.top());
}
