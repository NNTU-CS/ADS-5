// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int powerTen(int exp) {
  int value = 1;
  for (int i = 0; i < exp; i++) {
    value *= 10;
  }
  return value;
}

int strToNum(const std::string& str) {
  int value = 0;
  for (int i = 0; i < str.size(); i++) {
    value += (str[str.size() - 1 - i] - '0') * powerTen(i);
  }
  return value;
}

std::string infx2pstfx(const std::string& infix) {
  TStack<char, 100> stk;
  std::map<char, int> precedence = {{'+', 0}, {'-', 0}, {'*', 1}, {'/', 1},
                                    {'(', 2}, {')', -1}};
  std::string output;

  for (size_t i = 0; i < infix.size(); i++) {
    char ch = infix[i];
    if (ch >= '0' && ch <= '9') {
      output.push_back(ch);
      if (i + 1 == infix.size() ||
          !(infix[i + 1] >= '0' && infix[i + 1] <= '9')) {
        output.push_back(' ');
      }
    } else if (ch == '(') {
      stk.push(ch);
    } else if (ch == ')') {
      while (!stk.isEmpty() && stk.getTop() != '(') {
        output.push_back(stk.pop());
        output.push_back(' ');
      }
      if (!stk.isEmpty()) {
        stk.pop();
      } else {
        throw std::string("Скобки не парные");
      }
    } else if (precedence.find(ch) != precedence.end()) {
      while (!stk.isEmpty() && stk.getTop() != '(' &&
             precedence[ch] <= precedence[stk.getTop()]) {
        output.push_back(stk.pop());
        output.push_back(' ');
      }
      stk.push(ch);
    } else {
      throw std::string("Неверный символ в формуле");
    }
  }

  while (!stk.isEmpty()) {
    char last = stk.pop();
    if (last == '(') {
      throw std::string("Скобки не парные");
    }
    output.push_back(last);
    output.push_back(' ');
  }

  if (!output.empty() && output.back() == ' ') {
    output.pop_back();
  }

  return output;
}

int eval(const std::string& postfix) {
  TStack<int, 100> stk;
  std::string digits;

  for (size_t i = 0; i < postfix.size(); i++) {
    char ch = postfix[i];
    if (ch >= '0' && ch <= '9') {
      digits.push_back(ch);
    } else if (ch == ' ') {
      if (!digits.empty()) {
        stk.push(strToNum(digits));
        digits.clear();
      }
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      if (stk.isEmpty()) {
        throw std::string("Ошибка в постфиксной записи");
      }
      int b = stk.pop();
      if (stk.isEmpty()) {
        throw std::string("Ошибка в постфиксной записи");
      }
      int a = stk.pop();
      int interim;
      switch (ch) {
        case '+':
          interim = a + b;
          break;
        case '-':
          interim = a - b;
          break;
        case '*':
          interim = a * b;
          break;
        case '/':
          if (b == 0) {
            throw std::string("Делить на ноль нельзя");
          }
          interim = a / b;
          break;
        default:
          throw std::string("Непонятная операция");
      }
      stk.push(interim);
    } else {
      throw std::string("Неверный знак в постфиксе");
    }
  }

  if (!digits.empty()) {
    stk.push(strToNum(digits));
  }

  if (stk.isEmpty()) {
    throw std::string("Ошибка в постфиксной записи");
  }

  int answer = stk.pop();
  if (!stk.isEmpty()) {
    throw std::string("Ошибка в постфиксной записи");
  }

  return answer;
}
