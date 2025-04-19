// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  std::string res;
  TStack<char, 100> st;
  size_t i = 0;

  while (i < inf.size()) {
    char c = inf[i];

    if (isdigit(c)) {
      while (i < inf.size() && isdigit(inf[i])) {
        res += inf[i++];
      }
      res += ' ';
    } else if (c == '(') {
      st.push(c);
      i++;
    } else if (c == ')') {
      while (!st.isEmpty() && st.topElem() != '(') {
        res += st.pop();
        res += ' ';
      }
      if (!st.isEmpty()) {
        st.pop();
      }
      i++;
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!st.isEmpty() && priority(st.topElem()) >= priority(c)) {
        res += st.pop();
        res += ' ';
      }
      st.push(c);
      i++;
    } else {
      i++;
    }
  }

  while (!st.isEmpty()) {
    res += st.pop();
    res += ' ';
  }

  return res;
}

int eval(const std::string& post) {
  TStack<int, 100> st;
  std::istringstream iss(post);
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0])) {
      st.push(std::stoi(token));
    } else {
      int b = st.pop();
      int a = st.pop();
      if (token == "+") {
        st.push(a + b);
      } else if (token == "-") {
        st.push(a - b);
      } else if (token == "*") {
        st.push(a * b);
      } else if (token == "/") {
        if (b == 0) {
          throw std::runtime_error("Division by zero");
        }
        st.push(a / b);
      }
    }
  }

  return st.pop();
}
