// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
  // добавьте код стека
 private:
    T data[100];
    int top;

 public:
    TStack() : top(-1) {}
    void push(T val) {
        if (!isFull())
            data[++top] = val;
        else
            throw std::string("Full");
    }
    T get() const {
        return data[top];
    }
    T pop() {
        if (isEmpty()) {
            throw std::string("Empty");
        } else {
            return data[top--];
        }
    }
    bool isEmpty() const {
        return top == -1;
    }
    bool isFull() const {
        return top == size - 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
#include <map>
#include "tstack.h"

int Priority(char oper) {
    if (oper == '+' || oper == '-') return 1;
    if (oper == '*' || oper == '/') return 2;
    return 0;
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

std::string infx2pstfx(std::string inf) {
  // добавьте код
  return std::string("");
    std::string postfix;
    TStack<char, 100> stack;
    for (char c : inf) {
        if (isdigit(c)) {
            postfix = postfix + c + ' ';
        } else if (c == '(') {
            stack.push(c);
        } else if (isOperator(c)) {
            while (!stack.isEmpty() && Priority(stack.get()) >= Priority(c)) {
                postfix = postfix + stack.get() + ' ';
                stack.pop();
            }
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.get() != '(') {
                postfix = postfix + stack.get() + ' ';
                stack.pop();
            }
            stack.pop();
        }
    }
    while (!stack.isEmpty()) {
        postfix = postfix + stack.get() + ' ';
        stack.pop();
    }
    if (!postfix.empty()) {
        postfix.pop_back();
    }
    return postfix;
}

int eval(std::string pref) {
  // добавьте код
  return 0;
int eval(std::string post) {
    TStack<int, 100> stack;
    std::string Number;
    for (char c : post) {
        if (isdigit(c)) {
            Number += c;
        } else if (Number != "") {
            stack.push(std::atoi(Number.c_str()));
            Number = "";
        }
        if (isOperator(c)) {
            int val2 = stack.get();
            stack.pop();
            int val1 = stack.get();
            stack.pop();
            switch (c) {
            case '+':
                stack.push(val1 + val2);
                break;
            case '-':
                stack.push(val1 - val2);
                break;
            case '*':
                stack.push(val1 * val2);
                break;
            case '/':
                stack.push(val1 / val2);
                break;
            }
        }
    }
    if (Number != "") {
        stack.push(std::atoi(Number.c_str()));
    }
    return stack.get();
}
