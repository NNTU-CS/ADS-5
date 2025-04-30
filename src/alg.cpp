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

int eval(const std::string& post) {
  TStack<int, 100> num_stack;
  std::string curr_num = "";
  for (int idx = 0; idx < post.length(); idx++) {
    char curr_char = post[idx];
    if (is_number_symbol(curr_char)) {
      curr_num += curr_char;
    } else if (curr_char == ' ') {
      if (!curr_num.empty()) {
        int num_val = 0;
        for (int j = 0; j < curr_num.length(); j++) {
          num_val = num_val * 10 + (curr_num[j] - '0');
        }
        num_stack.push(num_val);
        curr_num = "";
      }
    } else if (is_math_symbol(curr_char)) {
      if (num_stack.is_empty()) continue;
      int right_operand = num_stack.top();
      num_stack.pop();
      if (num_stack.is_empty()) continue;
      int left_operand = num_stack.top();
      num_stack.pop();
      int res = 0;
      switch (curr_char) {
      case '+': res = left_operand + right_operand; break;
      case '-': res = left_operand - right_operand; break;
      case '*': res = left_operand * right_operand; break;
      case '/':
        if (right_operand != 0) {
          res = left_operand / right_operand;
        }
        break;
      }
      num_stack.push(res);
    }
  }
  if (!curr_num.empty()) {
    int num_val = 0;
    for (int j = 0; j < curr_num.length(); j++)
      num_val = num_val * 10 + (curr_num[j] - '0');
    num_stack.push(num_val);
  }
  return num_stack.top();
}
