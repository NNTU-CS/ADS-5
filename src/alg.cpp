// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"
int prior_op(char str) {
        if (str == '+' || str == '-')
                return 1;
        else if (str == '*' || str == '/')
                return 2;
        return 0;
}
std::string infx2pstfx(std::string inf) {
  // добавьте код
  TStack<char, 100> stack;
  std::string post_str;
  for (int i = 0; inf[i] != '\0'; i++) {
    if (inf[i] == '+' || inf[i] == '-' ||
    inf[i] == '*' || inf[i] == '/') {
      while (!stack.empty() && prior_op(stack.got()) >= prior_op(inf[i])) {
               post_str = post_str + stack.got() + ' ';
               stack.pop();
                }
        stack.posh(inf[i]);
        } else if (isdigit(inf[i])) {
                post_str = post_str + inf[i] + ' ';
        } else if (inf[i] == '(') {
                stack.posh(inf[i]);
        } else if (inf[i] == ')') {
                while (!stack.empty() && stack.got() != '(') {
                        post_str = post_str + stack.got() + ' ';
                        stack.pop();
                }
                stack.pop();
        }
}
while (!stack.empty()) {
        post_str = post_str + stack.got() + ' ';
        stack.pop();
}
        post_str.pop_back();
return post_str;
}
int eval(std::string post) {
  // добавьте код
  TStack<int, 100> stack;
for (int i = 0; post[i] != '\0'; i++) {
  if (std::isdigit(post[i])) {
                stack.posh(post[i] - '0');
  } else if (post[i] == '+' || post[i] == '-' ||
          post[i] == '*' || post[i] == '/') {
                int b = stack.pop();
                int a = stack.pop();
                if (post[i] == '+')
                        stack.posh(a + b);
                else if (post[i] == '-')
                        stack.posh(a - b);
                else if (post[i] == '*')
                        stack.posh(a * b);
                else if (post[i] == '/')
                        stack.posh(a / b);
        }
}
return stack.pop();
return 0;
}
