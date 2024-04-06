// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int get_priority(char element) {
  if (element == '(') {
    return 0;
  } else if (element == ')') {
    return 1;
  } else if ((element == '+') || (element == '-')) {
    return 2;
  } else if ((element == '*') || (element == '/')) {
    return 3;
  } else {
    throw "Unknown!";
  }
}

std::string infx2pstfx(const std::string inf) {
  std::string postfics = "";
  TStack<char, 100> stack1;
  for (int i = 0; i < inf.size(); i++) {
    char c = inf[i];
    if (isdigit(c)) {
      int operands = 0;
      while (i < inf.size() && isdigit(inf[i])) {
        operands = operands * 10 + (inf[i] - '0');
        i++;
      }
      i--;
      postfics += std::to_string(operands) + " ";
    } else if (isalpha(c)) {
      postfics += c;
      postfics += " ";
    } else if (c == '(') {
      stack1.push(c);
    } else if (c == ')') {
      while (!stack1.isEmpty() && stack1.watch() != '(') {
        postfics += stack1.pop();
        postfics += ' ';
      }
      if (!stack1.isEmpty() && stack1.watch() == '(') {
        stack1.pop();
      }
    } else if (isOperator(c)) {
      while (!stack1.isEmpty() &&
        isPriority(stack1.watch()) >= isPriority(c)) {
        postfics += stack1.pop();
        postfics += ' ';
      }
      stack1.push(c);
    }
  }
  while (!stack1.isEmpty()) {
    postfics += stack1.pop();
    postfics += ' ';
  }
  if (!postfics.empty() && postfics[postfics.size() - 1] == ' ') {
    postfics.pop_back();
  }
  return postfics;
}

int eval(const std::string pref) {
  TStack<int, 100> stack2;
  for (int i = 0; i < pref.size(); i++) {
    if (isdigit(pref[i])) {
      int operands = 0;
      while (i < pref.size() && isdigit(pref[i])) {
        operands = operands * 10 + (pref[i] - '0');
        i++;
      }
      i--;
      stack2.push(operands);
    } else if (isOperator(pref[i])) {
      int operands2 = stack2.pop();
      int operands1 = stack2.pop();
      if (pref[i] == '+') {
        stack2.push(operands1 + operands2);
      } else if (pref[i] == '-') {
        stack2.push(operands1 - operands2);
      } else if (pref[i] == '*') {
        stack2.push(operands1 * operands2);
      } else if (pref[i] == '/') {
        stack2.push(operands1 / operands2);
      }
    }
  }
  return stack2.pop();
}
