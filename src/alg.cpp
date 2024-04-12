// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include "alg.h"

std::string infx2pstfx(std::string inf) {
    TStack<char, 100>stack1;
    std::string postfix;
    for (int i = 0; i < inf.length(); i++) {
      if (inf[i] == '(') {
        stack1.push(inf[i]);
      } else if ((inf[i] >= '0') && (inf[i] <= '9')) {
        postfix += inf[i];
        postfix += ' ';
      } else if (inf[i] == ')') {
        while ((!stack1.isEmpty()) && (stack1.get() != '(')) {
          postfix += stack1.pop();
          postfix += ' ';
      }
        if (stack1.get() == '(') {
          stack1.pop();
              }
        } else if (inf[i] == '+' || inf[i] == '-') {
if (!stack1.isEmpty()) {
                switch (stack1.get()) {
                    case '*': {
                        postfix += '*';
                        postfix += ' ';
                        stack1.pop();
                        break;
                    }
                    case '/': {
                        postfix += '/';
                        postfix += ' ';
                        stack1.pop();
                        break;
                    }
                    case '+': {
                        postfix += '+';
                        postfix += ' ';
                        stack1.pop();
                        break;
                    }
                    case '-': {
                        postfix += '-';
                        postfix += ' ';
                      stack1.pop();
                        break;
                    }
                }
          stack1.push(inf[i]);
} else {
  stack1.push(inf[i]);
}
      } else if (inf[i] == '*' || inf[i] == '/') {
        if (!stack1.isEmpty()) {
          switch (stack1.get()) {
            case '*': {
              postfix += '*';
              postfix += ' ';
              stack1.pop();
              break;
            }
            case '/': {
              postfix += '/';
              postfix += ' ';
              stack1.pop();
              break;
            }
          }
          stack1.push(inf[i]);
        } else {
          stack1.push(inf[i]);
        }
      }
    }
    if (!stack1.isEmpty()) {
      while (!stack1.isEmpty()) {
      postfix += stack1.pop();
        postfix += ' ';
    }
}
    std::string postfix2;
    for (int i = 0; i < (postfix.length() - 1); i++) {
        postfix2 += postfix[i];
    }
    return postfix2;
      }
int eval(std::string pref) {
    TStack<int, 100> stack2;
    for (int i = 0; i < pref.length(); i++) {
        if ((pref[i] >= '0') && (pref[i] <= '9')) {
            stack2.push(pref[i] - '0');
        } else if (pref[i] != ' ' || (pref[i] < '0') && (pref[i] > '9')) {
            int operand2 = stack2.pop();
            int operand1 = stack2.pop();
            switch (pref[i]) {
                case '+':
                    stack2.push(operand1 + operand2);
                    break;
                case '-':
                    stack2.push(operand1 - operand2);
                    break;
                case '*':
                    stack2.push(operand1 * operand2);
                    break;
                case '/':
                    stack2.push(operand1 / operand2);
                    break;
            }
        }
    }
    return stack2.get();
}
