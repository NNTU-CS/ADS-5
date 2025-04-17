// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

static const std::map<char, int> kPrecedenceMap = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}
};

static bool IsOperator(char c) {
  return kPrecedenceMap.find(c) != kPrecedenceMap.end();
}

std::string infx2pstfx(const std::string& inf) {
  std::string output;
  TStack<char, 100> op_stack;

  for (size_t i = 0; i < inf.length(); ++i) {
    char c = inf[i];

    if (c == ' ') continue;

    if (c >= '0' && c <= '9') {
      while (i < inf.length() && inf[i] >= '0' && inf[i] <= '9') {
        output += inf[i++];
      }
      output += ' ';
      --i;
    } else if (c == '(') {
      op_stack.push(c);
    } else if (c == ')') {
      while (!op_stack.empty() && op_stack.top() != '(') {
        output += op_stack.top();
        output += ' ';
        op_stack.pop();
      }
      if (!op_stack.empty() && op_stack.top() == '(') {
        op_stack.pop();
      }
    } else if (IsOperator(c)) {
      while (!op_stack.empty() && IsOperator(op_stack.top()) &&
             kPrecedenceMap.at(op_stack.top()) >= kPrecedenceMap.at(c)) {
        output += op_stack.top();
        output += ' ';
        op_stack.pop();
      }
      op_stack.push(c);
    }
  }

  while (!op_stack.empty()) {
    output += op_stack.top();
    output += ' ';
    op_stack.pop();
  }

  if (!output.empty() && output.back() == ' ') {
    output.pop_back();
  }

  return output;
}

int eval(const std::string& pref) {
  TStack<int, 100> val_stack;
  std::string token;
  size_t i = 0;

  while (i < pref.length()) {
    if (pref[i] == ' ') {
      ++i;
      continue;
    }

    token.clear();
    while (i < pref.length() && pref[i] != ' ') {
      token += pref[i++];
    }

    if (token.size() == 1 && IsOperator(token[0])) {
      int right = val_stack.top();
      val_stack.pop();
      int left = val_stack.top();
      val_stack.pop();
      int result = 0;

      switch (token[0]) {
        case '+': result = left + right; break;
        case '-': result = left - right; break;
        case '*': result = left * right; break;
        case '/': result = left / right; break;
      }

      val_stack.push(result);
    } else {
      val_stack.push(std::stoi(token));
    }
  }

  return val_stack.top();
}
