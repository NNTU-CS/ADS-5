// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include <sstream>
#include "tstack.h"

int precedence(char oper) {
    switch (oper) {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default: return 0;
    }
}

std::string infx2pstfx(const std::string& inf) {
  std::string output;
  TStack<char, 100> operStack;
  for (size_t j = 0; j < inf.length(); j++) {
    char sym = inf[j];
    if (sym == ' ') {
        continue;
    }

    if (std::isdigit(sym)) {
        while (j < inf.length() && std::isdigit(inf[j])) {
            output.push_back(inf[j]);
            j++;
        }
        j--;
        output.push_back(' ');
    } else if (sym == '(') {
        operStack.push(sym);
    } else if (sym == ')') {
        while (!operStack.empty() && operStack.top() != '(') {
            output.push_back(operStack.top());
            output.push_back(' ');
            operStack.pop();
        }
        if (!operStack.empty() && operStack.top() == '(') {
            operStack.pop();
        } else {
            throw std::runtime_error("erroneously");
        }
    } else if (sym == '+' || sym == '-' || sym == '*' || sym == '/') {
        while (!operStack.empty() && precedence(operStack.top()) >=
            precedence(sym)) {
            output.push_back(operStack.top());
            output.push_back(' ');
            operStack.pop();
        }
        operStack.push(sym);
    } else {
        throw std::runtime_error(std::string("Invalid character") + sym);
    }
  }
  while (!operStack.empty()) {
    if (operStack.top() == '(' || operStack.top() == ')') {
        throw std::runtime_error("erroneously");
    }
    output.push_back(operStack.top());
    output.push_back(' ');
    operStack.pop();
  }
  if (!output.empty() && output.back() == ' ') {
    output.pop_back();
  }
  return output;
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
                throw std::runtime_error("few operands");
            }

            int operand2 = cntStack.top();
            cntStack.pop();
    
            if (cntStack.empty()) {
                throw std::runtime_error("few operands");
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
                        throw std::runtime_error("Division by zero");
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    throw std::runtime_error("error");
            }
            cntStack.push(result);
        } else {
            throw std::runtime_error("wrong token: " + token);
        }
    }

    if (cntStack.empty()) {
        throw std::runtime_error("stack is empty");
    }

    int res = cntStack.top();
    cntStack.pop();

    if (!cntStack.empty()) {
        throw std::runtime_error("erroneously");
    }

    return res;
}
