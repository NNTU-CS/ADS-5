// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int pr(char e) {
    if (e == '+'  || e == '-')
        return 1;
    if (e == '*'  || e == '/')
        return 2;
    return 0;
}

std::string infx2pstfx(std::string inf) {
  // добавьте код
    std::string dig;
    int counter = 0;
    tstack <char, 100> post;
    for (char i : inf) {
        if (i >= '0' && i <= '9') {
            counter++;
            if (counter == 1) {
                dig += i;
                continue;
            }
            dig = dig + ' ' + i;
        } else if (i == '+' || i == '-' || i == '*' ||
            i == '/' ||  i == '(' || i == ')') {
            if (i == '(') {
                post.push(i);
            } else if (post.empty()) {
                post.push(i);
            } else if (pr(i) > pr(post.get())) {
                post.push(i);
            } else if (i == ')') {
                while (post.get() != '(') {
                    dig = dig + ' ' + post.get();
                    post.pop();
                }
                post.pop();
            } else {
                int w = pr(i);
                int z = pr(post.get());
                while (!post.empty() && w <= z) {
                    dig = dig + ' ' + post.get();
                    post.pop();
                }
                post.push(i);
            }
        }
    }
    while (!post.empty()) {
        dig = dig + ' ' + post.get();
        post.pop();
    }
    return dig;
}

int eval(std::string pref) {
  // добавьте код
    tstack <int, 100> num;
    for (char k : pref) {
        if (k >= '0' && k <= '9') {
            num.push(k - '0');
        } else if (pr(k)) {
            int z = num.get();
            num.pop();
            int w = num.get();
            num.pop();
            switch (k) {
            case '+':
                num.push(z + w);
                break;
            case '-':
                num.push(w - z);
                break;
            case '*':
                num.push(z * w);
                break;
            case '/':
                num.push(w / z);
                break;
            default:
                continue;
            }
        } else {
            continue;
        }
    }
    return num.get();
}
