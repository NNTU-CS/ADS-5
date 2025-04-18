// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
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
    outS.push_back(Stack.top());
    outS.push_back(' ');
    stack.pop();
  }
  if (!outS.empty() && outS.back() == ' ') {
    outS.pop_back();
  }
  return outS;
}


int eval(const std::string& pref) {
    TStack<int, 100> cntStack;
    std::istringstream iss(pref);
    std::string token;
    while (iss >> token) {
        if (std::isdigit(token[0])) {
            int cnt = std::stoi(token);
            cntStack.push(cnt);
        } else if (token.length() == 1 &&
                   (token[0] == '+' || token[0] == '-' ||
                    token[0] == '*' || token[0] == '/')) {
            if (cntStack.empty()) {
                throw std::runtime_error("Err");
            }

            int operand2 = cntStack.top();
            cntStack.pop();

            if (cntStack.empty()) {
                throw std::runtime_error("Err");
            }

            int operand1 = cntStack.top();
            cntStack.pop();
            int result = 0;

            switch (token[0]) {
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
            cntStack.push(result);
        } else {
            throw std::runtime_error("Err");
        }
    }

    if (cntStack.empty()) {
        throw std::runtime_error("Empty");
    }

    int res = cntStack.top();
    cntStack.pop();

    if (!cntStack.empty()) {
        throw std::runtime_error("erroneously");
    }

    return res;
}
