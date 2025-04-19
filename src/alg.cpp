// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

bool is_math_operator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

int operation_priority(char op) {
  switch (op) {
  case '+': case '-': return 1;
  case '*': case '/': return 2;
  default: return 0;
  }
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> operators;
  std::string result = "";
  std::string digit_buffer = "";
  for (int i = 0; i < inf.length(); i++) {
    char current = inf[i];
    if (is_digit(current)) {
      digit_buffer += current;
      continue;
    }
    if (!digit_buffer.empty()) {
      result += digit_buffer + " ";
      digit_buffer = "";
    }
    if (current == '(') {
      operators.push(current);
    } else if (current == ')') {
      while (!operators.is_empty() && operators.peek() != '(') {
        result += operators.peek();
        result += " ";
        operators.pop();
      }
      if (!operators.is_empty()) {
        operators.pop();
      }
    } else if (is_math_operator(current)) {
      while (!operators.is_empty() && operators.peek() != '(' &&
        operation_priority(operators.peek()) >= operation_priority(current)) {
        result += operators.peek();
        result += " ";
        operators.pop();
      }
      operators.push(current);
    }
  }
  if (!digit_buffer.empty()) {
    result += digit_buffer + " ";
  }
  while (!operators.is_empty()) {
    if (operators.peek() != '(') {
      result += operators.peek();
      result += " ";
    }
    operators.pop();
  }
  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
  return result;
}

int eval(const std::string& pstfx) {
  TStack<int, 100> values;
  std::string number = "";
  for (int i = 0; i < pstfx.length(); i++) {
    char current = pstfx[i];
    if (is_digit(current)) {
      number += current;
    } 
    else if (current == ' ') {
      if (!number.empty()) {
        int value = 0;
        for (int j = 0; j < number.length(); j++) {
          value = value * 10 + (number[j] - '0');
        }
        values.push(value);
        number = "";
      }
    } 
    else if (is_math_operator(current)) {
      if (values.is_empty()) continue;
      int operand2 = values.peek();
      values.pop();
      if (values.is_empty()) continue;
      int operand1 = values.peek();
      values.pop();
      int result = 0;
      switch (current) {
      case '+': result = operand1 + operand2; break;
      case '-': result = operand1 - operand2; break;
      case '*': result = operand1 * operand2; break;
       case '/': 
        if (operand2 != 0) {
          result = operand1 / operand2;
        }
        break;
      }
      values.push(result);
    }
  }
  if (!number.empty()) {
    int value = 0;
    for (int j = 0; j < number.length(); j++)
      value = value * 10 + (number[j] - '0');
    values.push(value);
  }
  return values.peek();
}
