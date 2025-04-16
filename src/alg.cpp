// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int tPow(int g) {
  int temp = 1;
  for (int i = 0; i < g; i++)
    temp *= 10;
  return temp;
}

int to_int(const std::string& str) {
  int res = 0;
  for (int i = 0; i < str.size(); i++)
    res += (str[str.size() - 1 - i] - '0') * tPow(i);
  return res;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::map<char, int> pr = {
  {'+', 0},
  {'-', 0},
  {'*', 1},
  {'/', 1},
  {'(', 2}};
  std::string out;
  for (int i = 0; i < inf.size(); i++) {
    if (inf[i] >= '0' && inf[i] <= '9') {
      out.push_back(inf[i]);
      if (!(i != inf.size() - 1 && (inf[i + 1] >= '0' && inf[i + 1] <= '9')))
        out.push_back(' ');
    } else if (inf[i] == ')') {
        while (stack.getTop() != '(') {
          out.push_back(stack.pop());
          out.push_back(' ');
        }
        stack.pop();
    } else if (pr[inf[i]] == 0 && pr[stack.getTop()] == 1) {
        while (!stack.isEmpty() && pr[stack.getTop()] == 1) {
          out.push_back(stack.pop());
          out.push_back(' ');
        }
        stack.push(inf[i]);
    } else if (stack.isEmpty() ||
pr[inf[i]] == 0 ||
pr[inf[i]] > pr[stack.getTop()]) {
        stack.push(inf[i]);
    } else {
        while (!stack.isEmpty() && pr[inf[i]] <= pr[stack.getTop()]) {
          out.push_back(stack.pop());
          out.push_back(' ');
        }
        stack.push(inf[i]);
    }
  }

  while (!stack.isEmpty()) {
    out.push_back(stack.pop());
    out.push_back(' ');
  }

  if (out[out.size() - 1] == ' ')
    out.pop_back();

  return out;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack;
  std::string temp;
  int sum = 0;
  for (int i = 0; i < pref.size(); i++) {
    if (pref[i] >= '0' && pref[i] <= '9') {
    temp.push_back(pref[i]);
    } else if (pref[i] == ' ') {
        if (temp.size()) {
        stack.push(to_int(temp));
        temp = "";
        } else {
          continue;
        }
    } else {
        switch (pref[i]) {
          case '+':
          sum = stack.pop() + stack.pop();
          break;
          case '-':
          sum = (stack.pop() - stack.pop()) * -1;
          break;
          case '*':
          sum = stack.pop() * stack.pop();
          break;
          case '/':
          sum = stack.pop();
          sum = stack.pop() / sum;
          break;
          default:
          throw std::string("Undefined symbol");
        }
        stack.push(sum);
    }
  }
  return stack.pop();
}
