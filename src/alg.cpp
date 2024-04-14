// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T* ptr;
    int x;

 public:
    TStack() : x(0) {
        ptr = new T[size];
    }
    void pushup(const T& c) {
        if (size - 1 >= x) {
            ptr[x++] = c;
        } else {
            throw std::string("Fall !");
        }
    }
    T popback() {
        if (x > 0) {
            return ptr[--x];
        } else {
            throw std::string("Empty");
        }
    }
    bool IfZero() const {
        return x == 0;
    }
    T ElemUp() const {
        if (x > 0) {
            return ptr[x - 1];
        } else {
            throw std::string("Fall!");
        }
    }
};

#endif  // INCLUDE_TSTACK_H_
#include <string>
#include <map>
#include "tstack.h"
int prioty(char);
int schet(int, int, char);

std::string infx2pstfx(std::string inf) {
  // добавьте код
  return std::string("");
  TStack<char, 100> stack;
    std::string line = "";
    int flag = 0;
    try {
        for (char& n : inf) {
            if ((n >= '0') && (n <= '9')) {
                if (flag == 1) {
                    line = line + " " + n;
                    flag = 0;
                } else {
                    line = line + n;
                }
            } else {
                if (n == '(') {
                    stack.pushup(n);
                } else {
                    flag = 1;
                    if (stack.IfZero()) {
                        stack.pushup(n);
                    } else {
                        if (n == ')') {
                            while (stack.ElemUp() != '(') {
                                line = line + " " + stack.popback();
                            }
                            stack.popback();
                        } else {
                            if (prioty(n) > prioty(stack.ElemUp())) {
                                stack.pushup(n);
                            } else {
                                while ((!stack.IfZero()) &&
                                    (prioty(n) <= prioty(stack.ElemUp()))) {
                                    line = line + " " + stack.popback();
                                }
                                stack.pushup(n);
                            }
                        }
                    }
                }
            }
        }
        while (!stack.IfZero()) {
            line = line + " " + stack.popback();
        }
        return line;
    }
    catch (std::string maliniya) {
        return "Fall!";
    }
}

int eval(std::string pref) {
  // добавьте код
  return 0;
  std::string line = "";
    TStack<int, 100> stack1;
    int flag = 0;
    try {
        for (char& b : pref) {
            if (flag == 0) {
                if (('0' <= b) && (b <= '9')) {
                    line += b;
                } else {
                    if (line == "") {
                        int y = stack1.popback();
                        int x = stack1.popback();
                        int res = schet(x, y, b);
                        stack1.pushup(res);
                        flag = 1;
                    } else {
                        stack1.pushup(stoi(line));
                        line = "";
                    }
                }
            } else {
                flag = 0;
            }
        }
        return stack1.popback();
    }
    catch (std::string maliniya) {
        return -1;
    }
    return 0;
}

int prioty(char znak) {
    int pryoto = 0;
    switch (znak) {
    case '+':
        return 2;
    case '-':
        return 2;
    case '(':
        return 0;
    case '*':
        return 3;
    case '/':
        return 3;
    case ')':
        return 1;
    default:
        break;
    }
    return pryoto;
}

int schet(int x, int y, char znak) {
    switch (znak) {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    default:
        return 0;
    }
}

