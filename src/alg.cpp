// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "tstack.h"

int priority(char oper) {
    switch (oper) {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default: return 0;
    }
}
std::string infx2pstfx(const std::string& inf) {
    std::string outS;
  TStack<char, 100> stack;
  for (size_t j = 0; j < inf.length(); j++) {
    char symb = inf[j];
    if (symb == ' ') {
        continue;
    }

    if (std::isdigit(symb)) {
        while (j < inf.length() && std::isdigit(inf[j])) {
            outS.push_back(inf[j]);
            j++;
        }
        j--;
        outS.push_back(' ');
    } else if (symb == '(') {
        stack.push(symb);
    } else if (symb == ')') {
        while (!stack.isEmpty() && stack.top() != '(') {
            outS.push_back(stack.top());
            outS.push_back(' ');
            stack.pop();
        }
        if (!stack.isEmpty() && stack.top() == '(') {
            stack.pop();
        } else {
            throw std::runtime_error("Err");
        }
    } else if (symb == '+' || symb == '-' || symb == '*' || symb == '/') {
        while (!stack.isEmpty() && priority(stack.top()) >=
            priority(symb)) {
            outS.push_back(stack.top());
            outS.push_back(' ');
            stack.pop();
        }
        stack.push(symb);
    } else {
        throw std::runtime_error(std::string("Err") + symb);
    }
  }
  while (!stack.isEmpty()) {
    if (stack.top() == '(' || stack.top() == ')') {
        throw std::runtime_error("Err");
    }
    outS.push_back(stack.top());
    outS.push_back(' ');
    stack.pop();
  }
  if (!outS.empty() && outS.back() == ' ') {
    outS.pop_back();
  }
  return outS;
}
int eval(const std::string& pref) {
    TStack<int, 100> stack;
    std::istringstream iss(pref);
    std::string tok;
    while (iss >> tok) {
        if (std::isdigit(tok[0])) {
            int cnt = std::stoi(tok);
            stack.push(cnt);
        } else if (tok.length() == 1 &&
                   (tok[0] == '+' || tok[0] == '-' ||
                    tok[0] == '*' || tok[0] == '/')) {
            if (stack.isEmpty()) {
                throw std::runtime_error("Err");
            }
            int operand2 = stack.top();
            stack.pop();
            if (stack.isEmpty()) {
                throw std::runtime_error("Err");
            }
            int operand1 = stack.top();
            stack.pop();
            int result = 0;
            switch (tok[0]) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/':
                    if (operand2 == 0) {
                        throw std::runtime_error("Err");
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    throw std::runtime_error("Err");
            }
            stack.push(result);
        } else {
            throw std::runtime_error("Err");
        }
    }
    if (stack.isEmpty()) {
        throw std::runtime_error("Empty");
    }
    int res = stack.top();
    stack.pop();

    if (!stack.isEmpty()) {
        throw std::runtime_error("erroneously");
    }
    return res;
}
