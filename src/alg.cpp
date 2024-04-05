// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char c) {
    int priority = 0;
    switch (c) {
        case '(':
            priority = 0;
            break;
        case ')':
            priority = 1;
            break;
        case '+':
            priority = 2;
            break;
        case '-':
            priority = 2;
            break;
        case '*':
            priority = 3;
            break;
        case '/':
            priority = 3;
            break;
        default:
            break;
    }
    return priority;
}

int calc(int x, int y, char c) {
    switch (c) {
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

std::string infx2pstfx(std::string inf) {
    std::string post = "";
    TStack<char, 100> stack1;
    int flag = 0;
    try {
        for (char& c : inf) {
            if (('0' <= c) && (c <= '9')) {
                if (flag == 1) {
                    post = post + " " + c;
                    flag = 0;
                } else {
                    post = post + c;
                }
            } else {
                if (c == '(') {
                    stack1.push(c);
                } else {
                    flag = 1;
                    if (stack1.isEmpty()) {
                        stack1.push(c);
                    } else {
                        if (c == ')') {
                            while (stack1.get() != '(') {
                                post = post + " " + stack1.pop();
                            }
                            stack1.pop();
                        } else {
                            if (priority(c) > priority(stack1.get())) {
                                stack1.push(c);
                            } else {
                                while ((!stack1.isEmpty()) &&
                                    (priority(c) <= priority(stack1.get()))) {
                                    post = post + " " + stack1.pop();
                                }
                                stack1.push(c);
                            }
                        }
                    }
                }
            }
        }
        while (!stack1.isEmpty()) {
            post = post + " " + stack1.pop();
        }
        return post;
    }
    catch (std::string ex) {
        return "ERROR";
    }
}

int eval(std::string post) {
    std::string str = "";
    TStack<int, 100> stack2;
    int flag = 0;
    try {
        for (char& c : post) {
            if (flag == 0) {
                if (('0' <= c) && (c <= '9')) {
                    str += c;
                } else {
                    if (str == "") {
                        int b = stack2.pop();
                        int a = stack2.pop();
                        int result = calc(a, b, c);
                        stack2.push(result);
                        flag = 1;
                    } else {
                        stack2.push(stoi(str));
                        str = "";
                    }
                }
            } else {
                flag = 0;
            }
        }
        return stack2.pop();
    }
    catch (std::string ex) {
        return -1;
    }
}
