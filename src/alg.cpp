// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char operation) {
  switch (operation) {
    case '+':
      return 1;
      break;
    case '-':
      return 1;
      break;
    case '*':
      return 2;
      break;
    case '/':
      return 2;
      break;
    default:
      return 0;
      break;
  }
}
bool IsNumber(char symbol) {
  if ((symbol >= '0') && (symbol <= '9')) return true;
  return false;
}
bool IsOperation(char symbol) {
  if ((symbol >= 40) && (symbol <= 43)) return true;
  if ((symbol == 45) || (symbol == 47)) return true;
  return false;
}
std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack1;
  std::string res;
  for (int i = 0; i < inf.length(); i++) {
    if (IsNumber(inf[i])) {
      res += inf[i];
      if (i < inf.length() - 1) {
        if (!IsNumber(inf[i + 1])) res += ' ';
      }
    } else if (IsOperation(inf[i])) {
        if (inf[i] == '(') {
          stack1.push(inf[i]);
        } else if (stack1.IsEmpty()) {
            stack1.push(inf[i]);
        } else if (inf[i] == ')') {
            while ((!stack1.IsEmpty()) && (stack1.get() != '(')) {
              res += stack1.pop();
              if (i != inf.length() - 1) {
                res += " ";
              }
            }
            stack1.pop();
        } else if (prioritet(inf[i]) > prioritet(stack1.get())) {
            stack1.push(inf[i]);
        } else if (prioritet(inf[i]) <= prioritet(stack1.get())) {
            while ((!stack1.IsEmpty()) &&
                  (prioritet(inf[i]) <= prioritet(stack1.get()))) {
              res += stack1.pop();
              if (i != inf.length() - 1) {
                res += " ";
              }
            }
            stack1.push(inf[i]);
         }
    }
}
  while (!stack1.IsEmpty()) {
    res += ' ';
    res += stack1.pop();
  }
  return res;
}
int eval(std::string post) {
  TStack<char, 100> stack2;
  std::string str;
  char res;
  for (int i = 0; i < post.length(); i++) {
    if (IsNumber(post[i])) {
      str += post[i];
      if (i < post.length() - 1) {
        if (post[i + 1] == ' ') {
          res = std::stoi(str);
          stack2.push(res);
          str = "";
        }
      }
    } else if (IsOperation(post[i])) {
        int el1 = stack2.pop();
        int el2 = stack2.pop();
        switch (post[i]) {
          case '+':
            stack2.push(el1 + el2);
            break;
          case '-':
            stack2.push(el2 - el1);
            break;
          case '*':
            stack2.push(el1 * el2);
            break;
          case '/':
            stack2.push(el2 / el1);
            break;
        }
    }
  }
  return stack2.pop();
}
