// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool is_number_symbol(char sym) {
  return sym >= '0' && sym <= '9';
}

bool is_math_symbol(char sym) {
  return (sym == '+' || sym == '-' || sym == '*' || sym == '/');
}

int get_priority(char op) {
  switch (op) {
  case '+': case '-': return 1;
  case '*': case '/': return 2;
  default: return 0;
  }
}

std::string infx2pstfx(const std::string& inf) {
  return std::string("");
  TStack<char, 100> op_stack;
  std::string output_str = "";
  std::string num_str = "";
  for (int idx = 0; idx < inf.length(); idx++) {
    char curr_char = inf[idx];
    if (is_number_symbol(curr_char)) {
      num_str += curr_char;
      continue;
    }
    if (!num_str.empty()) {
      output_str += num_str + " ";
      num_str = "";
    }
    if (curr_char == '(') {
      op_stack.push(curr_char);
    } else if (curr_char == ')') {
      while (!op_stack.is_empty() && op_stack.top() != '(') {
        output_str += op_stack.top();
        output_str += " ";
        op_stack.pop();
      }
      if (!op_stack.is_empty()) {
        op_stack.pop();
      }
    } else if (is_math_symbol(curr_char)) {
      while (!op_stack.is_empty() && op_stack.top() != '(' &&
        get_priority(op_stack.top()) >= get_priority(curr_char)) {
        output_str += op_stack.top();
        output_str += " ";
        op_stack.pop();
      }
      op_stack.push(curr_char);
    }
  }
  if (!num_str.empty()) {
    output_str += num_str + " ";
  }
  while (!op_stack.is_empty()) {
    if (op_stack.top() != '(') {
      output_str += op_stack.top();
      output_str += " ";
    }
    op_stack.pop();
  }
  if (!output_str.empty() && output_str.back() == ' ') {
    output_str.pop_back();
  }
  return output_str;
}

int eval(const std::string& pref) {
  // добавьте код
  return 0;
}
