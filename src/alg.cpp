// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char x) {
    if (x == '(') {
        return 0;
    } else if (x == ')') {
        return 1;
    } else if (x == '+' || x == '-') {
        return 2;
    } else if (x == '*' || x == '/') {
        return 3;
    } else {
        return -1;
    }
}
std::string infx2pstfx(std::string inf) {
    std::string num, num1;
    TStack <char, 100> stack1;
    for (auto& x : inf) {
        int pr = prior(x);
        if (pr == -1) {
            num = num + x + ' ';
        } else {
            char znach = stack1.get();
            if (pr == 0 || prior(znach) < pr && stack1.isEmpty() || x == ')') {
                if (x == ')') {
                    while (prior(znach) >= pr) {
                        num = num + znach + ' ';
                        stack1.pop();
                        if (!stack1.isEmpty()) {
                            znach = stack1.get();
                        } else {
                            break;
                        }
                    }
                    stack1.pop();
                } else {
                    stack1.push(x);
                }
            } else {
                while (prior(znach) >= pr) {
                    num = num + znach + ' ';
                    stack1.pop();

                    if (!stack1.isEmpty()) {
                        znach = stack1.get();
                    } else {
                        break;
                    }
                }
                stack1.push(x);
            }
        }
    }
    while (!stack1.isEmpty()) {
        num = num + stack1.get() + ' ';
        stack1.pop();
    }
    for (int i = 0; i < num.size() - 1; i++) {
        num1 += num[i];
    }
    return num1;
}

int eval(std::string pref) {
  TStack<int, 100> stack1;
    std::string num = "";
    for (int i = 0; i < pref.size(); ++i) {
        if (prior(pref[i]) == -1) {
            if (pref[i] == ' ') {
                continue;
            } else if (isdigit(pref[i + 1])) {
                num += pref[i];
                continue;
            } else {
                num += pref[i];
                int value = atoi(num.c_str());
                stack1.push(value);
                num = "";
            }
        } else {
            int b = stack1.pop();
            int a = stack1.pop();
            switch (pref[i]) {
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
            }
        }
    }
    return stack1.get();
}
