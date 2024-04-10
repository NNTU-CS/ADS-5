// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int sraw(char u) {
    if (u == '+' || u == '-')
        return 1;
    if (u == '*' || u == '/')
        return 2;
    return 0;
}
std::string infx2pstfx(std::string inf) {
  // добавьте код
    std::string star;
    int zero = 0;
    TStack <char, 100> pstfx;
    for (char i : inf) {
        if (i >= '0' && i <= '9') {
            zero++;
            if (zero == 1) {
                star += i;
                continue;
            }
            star = star + ' ' + i;
        } else if (i == '+' || i == '-' || i == '*'\
            || i == '/' ||  i == '(' || i == ')') {
            if (i == '(') {
                pstfx.push(i);
            } else if (pstfx.isemp()) {
                pstfx.push(i);
            } else if (sraw(i) > sraw(pstfx.get())) {
                pstfx.push(i);
            } else if (i == ')') {
                while (pstfx.get() != '(') {
                    star = star + ' ' + pstfx.get();
                    pstfx.pop();
                }
                pstfx.pop();
            } else {
                int x = sraw(i);
                int y = sraw(pstfx.get());
                while (!pstfx.isemp() && x <= y) {
                    star = star + ' ' + pstfx.get();
                    pstfx.pop();
                }
                pstfx.push(i);
            }
        }
    }
    while (!pstfx.isemp()) {
        star = star + ' ' + pstfx.get();
        pstfx.pop();
    }
    return star;
}

int eval(std::string pref) {
  // добавьте код
    TStack <int, 100> number;
    for (char i : pref) {
        if (i >= '0' && i <= '9') {
            number.push(i - '0');
        } else if (sraw(i)) {
            int x = number.get();
            number.pop();
            int y = number.get();
            number.pop();
            switch (i) {
            case '+':
                number.push(x + y);
                break;
            case '-':
                number.push(y - x);
                break;
            case '*':
                number.push(x * y);
                break;
            case '/':
                number.push(y / x);
                break;
            default:
                continue;
            }
        } else {
            continue;
        }
    }
    return number.get();
}
