// Copyright 2025 NNTU-CS
#include <cctype>
#include <string>
#include <map>
#include <cmath>
#include "tstack.h"

int getPriority(char n) {
  switch (n) {
  case '*':
  case '/':
    return 2;
  case '+':
  case '-':
    return 1;
  case '^':
    return 3;
  default:
    return 0;
  }
}

std::string infx2pstfx(const std::string& inf) {
TStack<char, 100> stak;
  std::string postf;

  for (char x : inf) {
    if (isspace(x))
      continue;

    if (isdigit(x)) {
      postf = postf + x;
    } else if (x == '(') {
      stak.push(x);
    } else if (x == ')') {
      while (!stak.isEmpty() && stak.top() != '(') {
        postf = postf + ' ';
        postf = postf + stak.pop();;
      }
      stak.pop();
    } else {
      postf = postf + ' ';
      while (!stak.isEmpty() && getPriority(stak.top()) >= getPriority(x)) {
        postf = postf + stak.pop();
        postf = postf + ' ';
      }
      stak.push(x);
    }
  }
  while (!stak.isEmpty()) {
    postf = postf + ' ';
    postf = postf + stak.pop();;
  }
  return postf;
}

int eval(const std::string& pref) {
TStack<int, 100> stak;

  for (size_t i = 0; i < postf.size();) {
    if (isspace(postf[i])) {
      i++;
      continue;
    }

    if (isdigit(postf[i])) {
      int c = 0;
      while (i < postf.size() && isdigit(postf[i])) {
        c = c * 10 + (postf[i] - '0');
        i++;
      }
      stak.push(c);
    } else {
      int x2 = stak.pop();
      int x1 = stak.pop();

      switch (postf[i]) {
      case '^':
        stak.push(pow(x1, x2));
        break;
      case '/':
        stak.push(x1 / x2);
        break;
      case '+':
        stak.push(x1 + x2);
        break;
      case '-':
        stak.push(x1 - x2);
        break;
      case '*':
        stak.push(x1 * x2);
        break;

      }
      i++;
    }
  }
  return stak.pop();
}
