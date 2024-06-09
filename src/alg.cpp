// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
TStack<char, 100> stack1;
TStack<int, 100> stack2;
std::map<char, int> mapp {
      {'(', 0}, {')', 1}, {'+', 2}, {'-', 2}, {'*', 3}, {'/', 3}
};
std::string infx2pstfx(std::string inf) {
    std::string strinng = "";
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            strinng += inf[i];
            strinng += ' ';
        } else {
            if (stack1.isEmpty() == 1 || inf[i] == '('
                || mapp[inf[i]] > mapp[stack1.get()]) {
                stack1.push(inf[i]);
            } else if (inf[i] == ')') {
                while (stack1.get() != '(') {
                    strinng = strinng + stack1.pop() + ' ';
                }
                if (stack1.get() == '(') {
                    stack1.pop();
                }
            } else if (mapp[inf[i]] <= mapp[stack1.get()]) {
                char ch = stack1.pop();
                strinng = strinng + ch + ' ';
                stack1.push(inf[i]);
            }
        }
    }
    while (stack1.isEmpty() != 1) {
        strinng += stack1.pop();
        if (stack1.isEmpty() != 1) {
            strinng += ' ';
        }
    }
  return strinng;
}

int eval(std::string pref) {
    std::string stroka;
    char cha;
    for (char i : pref) {
        if (i >= '0' && i <= '9') {
            stroka += i;
        } else if (!stroka.empty() && i == ' ') {
            stack2.push(std::stoi(stroka));
            stroka.clear();
        } else {
            switch (i) {
                case '+': {
                    cha = stack2.pop();
                    stack2.push(stack2.pop() + cha);
                    break;
                }
                case '-': {
                    cha = stack2.pop();
                    stack2.push(stack2.pop() - cha);
                    break;
                }
                case '*': {
                    cha = stack2.pop();
                    stack2.push(stack2.pop() * cha);
                    break;
                }
                case '/': {
                    cha = stack2.pop();
                    stack2.push(stack2.pop() / cha);
                    break;
                }
            }
        }
    }
  return stack2.pop();
}
