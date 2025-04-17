// Copyright 2025 NNTU-CS
#include <cctype>
#include <map>
#include <sstream>
#include <string>

#include "tstack.h"

static int precendence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

static bool isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

std::string infx2pstfx(const std::string& inf) {
  std::string out;
  TStack<char, 128> ops;

  for (std::size_t i = 0; i < inf.size(); ++i) {
    char ch = inf[i];

    if (std::isspace(static_cast<unsigned char>(ch))) continue;
    if (std::isdigit(static_cast<unsigned char>(ch))) {
      while (i < inf.size() &&
             std::isdigit(static_cast<unsigned char>(inf[i]))) {
        out += inf[i++];
      }
      out += ' ';
      --i;
      continue;
    }

    if (ch == '(') {
      ops.push(ch);
      continue;
    }

    if (ch == ')') {
      while (!ops.empty() && ops.top() != '(') {
        out += ops.top();
        out += ' ';
        ops.pop();
      }
      if (!ops.empty() && ops.top() == '(') ops.pop();
      continue;
    }

    if (isOperator(ch)) {
      while (!ops.empty() && isOperator(ops.top()) &&
             precendence(ops.top()) >= precendence(ch)) {
        out += ops.top();
        out += ' ';
        ops.pop();
      }
      ops.push(ch);
      continue;
    }
  }

  while (!ops.empty()) {
    out += ops.top();
    out += ' ';
    ops.pop();
  }

  if (!out.empty() && out.back() == ' ') out.pop_back();
  return out;
}

int eval(const std::string& pref) {
  std::stringstream ss(pref);
  std::string token;
  TStack<int, 128> st;

  while (ss >> token) {
    if (token.size() == 1 && isOperator(token[0])) {
      if (st.size() < 2)
        throw std::runtime_error("incorrect postfix expression");
      int rhs = st.top();
      st.pop();
      int lhs = st.top();
      st.pop();
      int res = 0;

      switch (token[0]) {
        case '+':
          res = lhs + rhs;
          break;
        case '-':
          res = lhs - rhs;
          break;
        case '*':
          res = lhs * rhs;
          break;
        case '/':
          res = lhs / rhs;
          break;
      }
      st.push(res);
    } else {
      st.push(std::stoi(token));
    }
  }

  if (st.size() != 1) throw std::runtime_error("incorrect postfix expression");
  return st.top();
}
