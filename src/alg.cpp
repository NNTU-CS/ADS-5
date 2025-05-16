// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::map<char, int> priority {
{'(', 0}, {')', 1}, {'-', 2}, {'+', 2}, {'/', 3}, {'*', 3}
};
TStack<char, 100> stack1;
TStack<int, 100> stack2;

std::string infx2pstfx(const std::string& inf) {
  std::string str = "";
  for (int i = 0; i < inf.length(); i++) {
    if (isdigit(inf[i])) {
      str += inf[i];
      str += ' ';
    } else {
      if (inf[i] == '(') {
        stack1.push('(');
      } else if (inf[i] == ')') {
        while (!stack1.isEmp() && stack1.get() != '(') {
          str += stack1.pop();
          str += ' ';
        }
        if (!stack1.isEmp() && stack1.get() == '(') {
          stack1.pop(); // убираем '('
        }
      } else {
        while (!stack1.isEmp() && priority[inf[i]] <= priority[stack1.get()]) {
          str += stack1.pop();
          str += ' ';
        }
        stack1.push(inf[i]);
      }
    }
  }
  while (!stack1.isEmp()) {
    str += stack1.pop();
    str += ' ';
  }

  return str;
}

int eval(const std::string& pref) {
  std::string sP;
  char cP;
  for (char i : pref) {
    if ((i >= '0' && i <= '9')) {
       sP += i;
       } else if (!sP.empty() && i == ' ') {
      stack2.push(std::stoi(sP));
      sP.clear();
       } else {
      switch (i) {
        case '+' : {
          cP = stack2.pop();
          stack2.push(stack2.pop() + cP);
          break;
        }
          case '*' : {
            cP = stack2.pop();
            stack2.push(stack2.pop() * cP);
            break;
          }
             case '/': {
               cP = stack2.pop();
               stack2.push(stack2.pop() / cP);
               break;
             }
                case '-' : {
                  cP = stack2.pop();
                  stack2.push(stack2.pop() - cP);
                  break;
                }
      }
    }
  }
  return stack2.pop();
}
