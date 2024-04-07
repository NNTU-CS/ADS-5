// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char o) {
    switch (o) {
        case ('*'):
        case ('/'):
            return 2;
        case ('+'):
        case ('-'):
            return 1;
        default:
            return 0;
    }
}

std::string infx2pstfx(std::string inf) {
    std::string postfix;
    TStack<char, 100> stack;
    for (size_t i = 0; i < inf.size(); ++i) {
        char c = inf[i];
        if (c == ' ')
            continue;
        if ((c >= '0' && c <= '9')) {
            std::string number;
            while (i < inf.size() && (inf[i] >= '0' && inf[i] <= '9')) {
                number += inf[i];
                ++i;
            }
            postfix += number + ' ';
            --i;
        } else {
            switch (c) {
                case '(':
                    stack.push(c);
                    break;

                case ')':
                    while (!stack.isEmpty() && stack.get() != '(') {
                        postfix += stack.pop();
                    }
                    postfix += ' ';
                    stack.pop();
                    break;

                case '+':
                case '-':
                case '*':
                case '/':
                    while (!stack.isEmpty() &&
                    priority(stack.get()) >= priority(c)) {
                        postfix += stack.pop();
                        postfix += ' ';
                    }
                    stack.push(c);
                    break;
            }
        }
    }
    while (!stack.isEmpty()) {
        postfix += stack.pop();
        postfix += ' ';
    }

    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;
}

int eval(std::string post) {
    TStack<int, 100> stack;

    for (size_t i = 0; i < post.size(); ++i) {
        char c = post[i];
        if (isdigit(c)) {
            std::string number;
            while (i < post.size() && isdigit(post[i])) {
                number += post[i];
                ++i;
            }
            stack.push(std::stoi(number));
            --i;
        } else if (c != ' ') {
            int operand2 = stack.pop();
            int operand1 = stack.pop();
            switch (c) {
                case '+':
                    stack.push(operand1 + operand2);
                    break;
                case '-':
                    stack.push(operand1 - operand2);
                    break;
                case '*':
                    stack.push(operand1 * operand2);
                    break;
                case '/':
                    stack.push(operand1 / operand2);
                    break;
            }
        }
    }
    return stack.pop();
}
