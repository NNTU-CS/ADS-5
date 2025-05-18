// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

static int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> ops;
  std::ostringstream out;
  size_t i = 0;

  while (i < inf.size()) {
    char ch = inf[i];
    if (std::isdigit(ch)) {
      while (i < inf.size() && std::isdigit(inf[i])) {
        out << inf[i++];
      }
      out << ' ';
      --i;
    } else if (ch == '(') {
      ops.add(ch);
    } else if (ch == ')') {
      while (!ops.isVoid() && ops.getTop() != '(') {
        out << ops.remove() << ' ';
      }
      if (!ops.isVoid()) {
        ops.remove();
      }
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      while (!ops.isVoid() &&
             precedence(ops.getTop()) >= precedence(ch)) {
        out << ops.remove() << ' ';
      }
      ops.add(ch);
    }
    ++i;
  }

  while (!ops.isVoid()) {
    out << ops.remove() << ' ';
  }

  std::string res = out.str();
  if (!res.empty() && res.back() == ' ') {
    res.pop_back();
  }
  return res;
}

int eval(const std::string& post) {
  TStack<int, 100> vals;
  std::istringstream iss(post);
  std::string tok;

  while (iss >> tok) {
    if (std::isdigit(tok[0])) {
      vals.add(std::stoi(tok));
    } else {
      int r = vals.remove();
      int l = vals.remove();
      switch (tok[0]) {
        case '+': vals.add(l + r); break;
        case '-': vals.add(l - r); break;
        case '*': vals.add(l * r); break;
        case '/': vals.add(l / r); break;
      }
    }
  }
  return vals.remove();
}
