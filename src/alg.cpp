// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
static int get_prior(char elem) {
  if (elem == '(') {
    return 0;
  } else if (elem == ')') {
    return 1;
  } else if ((elem == '+') || (elem == '-')) {
    return 2;
  } else if ((elem == '*') || (elem == '/')) {
    return 3;
  } else {
    throw "Unknown Symbol";
  }
}


std::string infx2pstfx(std::string inf) {
  std::string out = "";
  TStack<char, 100> chars;
  for (int i = 0; i < inf.length(); i++) {
    if (isdigit(inf[i])) {
      out += inf[i];
      if (i != inf.length() - 1) {
        out += " ";
      }
    } else if (inf[i] == '(') {
      chars.push(inf[i]);
    } else if (chars.isempty()) {
      chars.push(inf[i]);
    } else if (inf[i] == ')') {
      while (true) {
        if (chars.isempty()) {
          break;
        } else if (chars.check() == '(') {
          break;
        }
        out += chars.pop();
        if (i != inf.length() - 1) {
          out += " ";
        }
      }
      chars.pop();
    } else if (get_prior(inf[i]) > get_prior(chars.check())) {
      chars.push(inf[i]);
    } else {
      while (true) {
        if (chars.isempty()) {
          break;
        } else if (!(get_prior(inf[i]) <= get_prior(chars.check()))) {
          break;
        }
        out += chars.pop();
        if (i != inf.length() - 1) {
          out += " ";
        }
      }
      chars.push(inf[i]);
    }
  }
  while (!chars.isempty()) {
    out += " ";
    out += chars.pop();
  }
  return out;
  return std::string("");
}

int eval(std::string pref) {
  std::string time = "";
  TStack<int, 100> ints;
  for (int i = 0; i < pref.length(); i++) {
    if (isdigit(pref[i])) {
      time += pref[i];
    } else if (time.length() && pref[i] == ' ') {
      ints.push(atoi(time.c_str()));
      time = "";
    } else if (pref[i] == '+') {
      int two = ints.pop();
      int one = ints.pop();
      ints.push(one + two);
    } else if (pref[i] == '-') {
      int two = ints.pop();
      int one = ints.pop();
      ints.push(one - two);
    } else if (pref[i] == '*') {
      int two = ints.pop();
      int one = ints.pop();
      ints.push(one * two);
    } else if (pref[i] == '/') {
      int two = ints.pop();
      int one = ints.pop();
      ints.push(one / two);
    }
  }
  return ints.pop();
  return 0;
}
