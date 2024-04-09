// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int prioty(char);
int schet(int, int, char);
std::string infx2pstfx(std::string);
int eval(std::string);

std::string infx2pstfx(std::string inf) {
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
