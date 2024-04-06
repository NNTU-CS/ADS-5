#include <iostream>
#include <string>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
TStack<char, 100> stack1;
  std::string spst;
    std::string spst;
  for (int i = 0; i < inf.length(); i++) {
      if (inf[i] >= '0' && inf[i] <= '9') {
          spst += inf[i];
          spst += ' ';
      } else if (inf[i] == '(') {
          stack1.push('(');
      } else if (inf[i] == ')') {
          while (!stack1.isempty() && stack1.get() != '(') {
              spst += stack1.get();
              spst += ' ';
              stack1.pop();
          }
          if (!stack1.isempty()) {
              stack1.pop();
          }
      } else {
          while (!stack1.isempty() && stack1.get() != '(' &&
          (inf[i] =='+' || stack1.get() =='*' || stack1.get() == '/')) {
              spst += stack1.get();
              spst += ' ';
              stack1.pop();
          }
          stack1.push(inf[i]);
      }
  }
  while (!stack1.isempty()) {
      spst += stack1.get();
      spst += ' ';
      stack1.pop();
  }
  if (!spst.empty()) {
      spst.erase(spst.size() - 1);
  }
  return spst;
}
