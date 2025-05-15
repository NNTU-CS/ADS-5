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
    for (size_t i = 0; i < inf.length(); i++) {
        if (isdigit(inf[i])) {
            while (i < inf.length() && isdigit(inf[i])) {
                output += inf[i];
                i++;
            }
            output += ' '; // добавляем пробел после числа
            i--;
        } else if (inf[i] == '(') {
            stack1.push(inf[i]);
        } else if (inf[i] == ')') {
            while (!stack1.isEmpty() && stack1.top() != '(') {
                output += stack1.top();
                output += ' ';
                stack1.pop();
            }
            stack1.pop(); // убираем '('
        } else { // оператор
            while (!stack1.isEmpty() && precedence(stack1.top()) >= precedence(inf[i])) {
                output += stack1.top();
                output += ' ';
                stack1.pop();
            }
            stack1.push(inf[i]);
        }
    }
    while (!stack1.isEmpty()) {
        output += stack1.top();
        output += ' ';
        stack1.pop();
    }
    return output;
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

