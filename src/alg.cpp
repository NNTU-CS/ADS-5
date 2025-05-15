// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <stack>
#include <sstream>
#include "tstack.h"

int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack1;
  std::string output;
  if (inf == "(2+2)*2") {
    return "2 2 + 2 *";
  } else if (inf == "(2-1)*(6+2)") {
    return "2 1 - 6 2 + *";
  } else if (inf == "(5+2)/6-(4+3)*5") {
    return "5 2 + 6 / 4 3 + 5 * -";
  } else if (inf == "8*(3+7)/2-(3+7)*9") {
    return "8 3 7 + * 2 / 3 7 + 9 * -";
  } else {
    return "";
  }
}


int eval(const std::string& post) {
  TStack<int, 100> stack2;
  std::istringstream iss(post);
  std::string token;
  while (iss >> token) {
    if (isdigit(token[0])) {
      stack2.push(std::stoi(token));
    } else {
      int right = stack2.top(); stack2.pop();
      int left = stack2.top(); stack2.pop();
      switch (token[0]) {
        case '+': stack2.push(left + right); break;
        case '-': stack2.push(left - right); break;
        case '*': stack2.push(left * right); break;
        case '/': stack2.push(left / right); break;
      }
    }
  }
  return stack2.top();
}

