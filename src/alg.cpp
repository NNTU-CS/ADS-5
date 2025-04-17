// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

static const std::map<char, int> kPrecedenceMap = {
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2}
};

static bool IsOperator(char c) {
  return kPrecedenceMap.find(c) != kPrecedenceMap.end();
}

static bool IsDigit(char c) {
  return c >= '0' && c <= '9';
}

std::string infx2pstfx(const std::string& inf) {
  std::string output;
  TStack<char, 100> op_stack;

  for (size_t i = 0; i < inf.length(); ++i) {
    char c = inf[i];

    if (c == ' ') continue;

    if (IsDigit(c)) {
      output += c;
      ++i;
      while (i < inf.length() && IsDigit(inf[i])) {
        output += inf[i++];
      }
      output += ' ';
      --i;
    } else if (c == '(') {
      op_stack.Push(c);
    } else if (c == ')') {
      while (!op_stack.IsEmpty() && op_stack.Top() != '(') {
        output += op_stack.Top();
        output += ' ';
        op_stack.Pop();
      }
      if (!op_stack.IsEmpty() && op_stack.Top() == '(') {
        op_stack.Pop();
      }
    } else if (IsOperator(c)) {
      while (!op_stack.IsEmpty() && IsOperator(op_stack.Top()) &&
             kPrecedenceMap.at(op_stack.Top()) >= kPrecedenceMap.at(c)) {
        output += op_stack.Top();
        output += ' ';
        op_stack.Pop();
      }
      op_stack.Push(c);
    }
  }

  while (!op_stack.IsEmpty()) {
    output += op_stack.Top();
    output += ' ';
    op_stack.Pop();
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
      int right = val_stack.Top(); val_stack.Pop();
      int left = val_stack.Top(); val_stack.Pop();
      int result = 0;
      switch (token[0]) {
        case '+': result = left + right; break;
        case '-': result = left - right; break;
        case '*': result = left * right; break;
        case '/': result = left / right; break;
      }
      val_stack.Push(result);
    } else {
      val_stack.Push(std::stoi(token));
    }
  }
  return val_stack.Top();
}
