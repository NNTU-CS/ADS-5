// Copyright 2021 NNTU-CS
#ifndef INCLUDE_ALG_H_
#define INCLUDE_ALG_H_

#include <string>
#include <queue>
#include "tstack.h"

int getPr(char inf) {
  switch (inf) {
  case '+':
  case '-':
    return 1;
    break;
  case '*':
  case '/':
    return 2;
    break;
  default:
    return 0;
    break;
  }
}

std::string infx2pstfx(std::string inf) {
  TStack<char, 100>stack1;
  std::string str = "";
  std::queue<char> queue;
  bool prior = false;
  for (int i = 0; i < inf.length(); ++i) {
    if (inf[i] >= '0' && inf[i] <= '9') {
      queue.push(inf[i]);
      continue;
    } else {
      if (inf[i] != '(') {
        queue.push(' ');
      }
      if (inf[i] == '(') {
        stack1.push(inf[i]);
        continue;
      }
      if (inf[i] == ')') {
        while ((!(stack1.isEmpty())) && !prior) {
          if (stack1.Top() == '(') {
            stack1.pop();
            prior = true;
            continue;
          }
          if (!(stack1.isEmpty())) {
            queue.push(stack1.Top());
            stack1.pop();
          }
        }
        prior = false;
        continue;
      }
      if (stack1.isEmpty() || ((stack1.Top()) == '(')) {
        stack1.push(inf[i]);
        continue;
      }
      if (getPr(inf[i]) > getPr(stack1.Top())) {
        stack1.push(inf[i]);
        continue;
      }
      if (getPr(inf[i]) <= getPr(stack1.Top())) {
        prior = true;
        while (!(stack1.isEmpty())&& prior) {
          if ((getPr(inf[i]) <= getPr(stack1.Top()))) {
            queue.push
            (stack1.Top());
            queue.push(' ');
            stack1.pop();
          }
          if ((getPr(inf[i]) > getPr(stack1.Top()))
                        || ((stack1.Top()) == '(')) {
            prior = false;
          }
        }
        stack1.push(inf[i]);
        continue;
      }
    }
  }
  while (!(stack1.isEmpty())) {
    if ((stack1.Top() == '(') || (stack1.Top() == ')')) {
      stack1.pop();
      continue;
    }
    queue.push(' ');
    queue.push(stack1.Top());
    stack1.pop();
  }
  while ((!(queue.empty()))) {
    str += queue.front();
    queue.pop();
  }
  return str;
}

int eval(std::string post) {
  int res = 0,a=0,b=0,sum=0;
  int num=0;
  bool por = false;
  std::stack<int> stack1;
  for (int i = 0; i < post.length(); ++i) {
    if (post[i] == ' ' && por) {
      stack1.push(sum);
      num = 0;
      sum = 0;
    }
    if (post[i] >= '0' && post[i] <= '9') {
      num++;
      por = true;
      if (num > 1) {
        sum *= 10;
        sum+= post[i] - 48;
      } else {
      sum += post[i] - 48;
      }
    } else if (post[i]!=' ') {
      por = false;
      b = stack1.top();
      stack1.pop();
      a = stack1.top();
      stack1.pop();
      switch (post[i]) {
      case '+':
        stack1.push(a + b);
        break;
      case '-':
        stack1.push(a - b);
        break;
      case '*':
        stack1.push(a * b);
        break;
      case '/':
        stack1.push(a / b);
        break;
      default:
        break;
      }
    }
  }
  res = stack1.top();
  return res;
}

#endif  // INCLUDE_ALG_H_
