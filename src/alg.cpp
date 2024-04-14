// Copyright 2021 NNTU-CS
#include <tstack.h>
#include <string>

TStack<char, 100> stack1;
TStack<int, 100> stack2;

std::string infx2pstfx(std::string inf) {
    std::string outputstr = "";
    for (char i : inf) {
        if (i >= '0' && i <= '9') {
            outputstr += i;
            outputstr += ' ';
        } else {
            if (stack1.isEmpty()) {
                stack1.push(i);
            } else if (i == '(') {
                stack1.push(i);
            } else if (i == ')') {
                while (stack1.get() != '(' && !stack1.isEmpty()) {
                    outputstr += stack1.pop();
                    outputstr += ' ';
                }
                if (stack1.get() == '(')
                    stack1.pop();
            } else if (i == '+' || i == '-') {
                if (!stack1.isEmpty()) {
                    switch (stack1.get()) {
                        case '-' : {
                            outputstr += stack1.pop();
                            outputstr += ' ';
                            break;
                        }
                        case '+' : {
                            outputstr += stack1.pop();
                            outputstr += ' ';
                            break;
                        }
                        case '*' : {
                            outputstr += stack1.pop();
                            outputstr += ' ';
                            break;
                        }
                        case '/' : {
                            outputstr += stack1.pop();
                            outputstr += ' ';
                            break;
                        }
                    }
                    stack1.push(i);
                } else if (stack1.isEmpty()) {
                    stack1.push(i);
                }
            } else if (i == '/' || i == '*') {
                if (!stack1.isEmpty()) {
                    switch (stack1.get()) {
                        case '*' : {
                            outputstr += stack1.pop();
                            outputstr += ' ';
                            break;
                        }
                        case '/' : {
                            outputstr += stack1.pop();
                            outputstr += ' ';
                            break;
                        }
                    }
                    stack1.push(i);
                } else if (stack1.isEmpty()) {
                    stack1.push(i);
                }
            }
        }
    }
    while (!stack1.isEmpty()) {
        if (stack1.get() == '(') {
            stack1.pop();
        }
        if (!stack1.isEmpty())
            outputstr += stack1.pop();
        outputstr += ' ';
    }
    outputstr.pop_back();
    return outputstr;
}

int eval(std::string post) {
    for (size_t i = 0; i < post.size(); ++i) {
        char c = post[i];
        if (c >= '0' && c <= '9') {
            std::string number;
            while (i < post.size() && (post[i] >= '0' && post[i] <= '9')) {
                number += post[i];
                ++i;
            }
            stack2.push(std::stoi(number));
            --i;
        } else if (c != ' ') {
            int op2 = stack2.pop();
            int op = stack2.pop();
            switch (c) {
                case '+':
                    stack2.push(op + op2);
                    break;
                case '-':
                    stack2.push(op - op2);
                    break;
                case '*':
                    stack2.push(op * op2);
                    break;
                case '/':
                    stack2.push(op / op2);
                    break;
            }
        }
    }
    return stack2.pop();
}
