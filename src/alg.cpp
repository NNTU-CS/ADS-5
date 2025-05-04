// Copyright 2025 NNTU-CS
#include <map>
#include <string>
#include "tstack.h"

int toInt(char arg) {
  switch (arg) {
    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    default:
      return 0;
  }
  return 0;
}

int pri(char target) {
  switch (target) {
    case '+':
      return 1;
    case '-':
      return 1;
    case '*':
      return 2;
    case '/':
      return 2;
    default:
      return 0;
  }
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string final;
  for (int i = 0; i < inf.size(); i++) {
    if (inf[i] == ' ') continue;
    if (std::isdigit(inf[i])) {
      while (i < inf.size() && std::isdigit(inf[i])) {
        final.push_back(inf[i]);
        i++;
      }
      i--;
      final.push_back(' ');
      continue;
    } else if (inf[i] == '(') {
      stack.push(inf[i]);
      continue;
    } else if (inf[i] == ')') {
      while (!stack.isEmpty() && stack.getTop() != '(') {
        final.push_back(stack.getTop());
        final.push_back(' ');
        stack.pop();
      }
      if (!stack.isEmpty() && stack.getTop() == '(')
        stack.pop();
      else
        throw std::string("Error!");
      continue;
    } else if (inf[i] == '+' || inf[i] == '-' || inf[i] == '*' ||
               inf[i] == '/') {
      while (!stack.isEmpty() && pri(inf[i]) <= pri(stack.getTop())) {
        final.push_back(stack.getTop());
        final.push_back(' ');
        stack.pop();
      }
      stack.push(inf[i]);
      continue;
    } else {
      throw std::string("Error!");
    }
  }
  while (!stack.isEmpty()) {
    if (stack.getTop() == '(' || stack.getTop() == ')')
      throw std::string("Error!");
    final.push_back(stack.getTop());
    stack.pop();
    final.push_back(' ');
  }
  if (!final.empty() && final.back() == ' ') final.pop_back();
  return final; }

int eval(const std::string& pref) {
  TStack<int, 100> stack;
  for (int i = 0; i < pref.size(); i++) {
    while (isdigit(pref[i])) {
      int number = toInt(pref[i]);
      stack.push(number);
      i++;
    }
    if (pref[i] == '+' || pref[i] == '-' || pref[i] == '*' || pref[i] == '/') {
      switch (pref[i]) {
        case '+': {
          int operand2 = 0, operand1 = 0;
          operand2 = stack.getTop();
          stack.pop();
          operand1 = stack.getTop();
          stack.pop();
          int result = operand1 + operand2;
          stack.push(result);
          break;
      }
        case '-': {
          int operand2 = 0, operand1 = 0;
          operand2 = stack.getTop();
          stack.pop();
          operand1 = stack.getTop();
          stack.pop();
          int result = operand1 - operand2;
          stack.push(result);
          break;
      }
      case '*': {
        int operand2 = 0, operand1 = 0;
        operand2 = stack.getTop();
        stack.pop();
        operand1 = stack.getTop();
        stack.pop();
        int result = operand1 * operand2;
        stack.push(result);
        break;
      }
      case '/': {
        int operand2 = 0, operand1 = 0;
        operand2 = stack.getTop();
        stack.pop();
        operand1 = stack.getTop();
        stack.pop();
        int result = operand1 / operand2;
        stack.push(result);
        break;
      }
      }
      continue;
    }
  }
  return stack.getTop();
}
