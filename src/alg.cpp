// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include <cctype>

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> temp;
  std::string res;
  std::map<char, int> priority = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0}, {')', 0}
  };

  for (int i = 0; i < inf.size(); ++i) {
    char c = inf[i];
    if (isspace(c)) continue;

    if (c == '(') {
      temp.push(c);
    } else if (c == ')') {
      while (!temp.isEmpty() && temp.get() != '(') {
        res.push_back(temp.get());
        res.push_back(' ');
        temp.pop();
      }
      if (!temp.isEmpty() && temp.get() == '(') {
        temp.pop();
      }
    } else if (priority.find(c) != priority.end()) {
      while (!temp.isEmpty()) {
        char top = temp.get();
        if (top == '(') break;
        if (priority[top] >= priority[c]) {
          res.push_back(top);
          res.push_back(' ');
          temp.pop();
        } else {
          break;
        }
      }
      temp.push(c);
    } else if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        res.push_back(inf[i]);
        ++i;
      }
      res.push_back(' ');
      --i;
    }
  }

  while (!temp.isEmpty()) {
    char op = temp.get();
    temp.pop();
    if (op == '(' || op == ')') continue;
    res.push_back(op);
    res.push_back(' ');
  }

  if (!res.empty() && res.back() == ' ') res.pop_back();
  return res;
}

int eval(const std::string& pref) {
  TStack<int, 100> st;
  for (int i = 0; i < pref.size(); ++i) {
    if (isspace(pref[i])) continue;

    if (isdigit(pref[i])) {
      int num = 0;
      while (i < pref.size() && isdigit(pref[i])) {
        num = num * 10 + (pref[i] - '0');
        ++i;
      }
      st.push(num);
      --i;
    } else {
      int b = st.get();
      st.pop();
      int a = st.get();
      st.pop();
      switch (pref[i]) {
        case '+':
          st.push(a + b);
          break;
        case '-':
          st.push(a - b);
          break;
        case '*':
          st.push(a * b);
          break;
        case '/':
          st.push(a / b);
          break;
      }
    }
  }
  return st.get();
}
