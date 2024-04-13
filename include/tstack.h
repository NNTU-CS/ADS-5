// Copyright 2021 NNTU-CS
#include <string>
#include <iostream>
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T* massive;
    int top;
 public:
    TStack() : top(0) {
        massive = new T[size];
    }
    void pushh(const T& c) {
        if (size - 1 >= top) {
            massive[top++] = c;
        }
        else {
            throw std::string("Stack overflow");
        }
    }
    T popp() {
        if (top > 0) {
            return massive[--top];
        }
        else {
            throw std::string("Stack is empty");
        }
    }
    bool isEmpty() const {
        return top == 0;
    }
    T getTopp() const {
        if (top > 0) {
            return massive[top - 1];
        }
        else {
            throw std::string("Stack is empty!");
        }
    }
};
#endif  // INCLUDE_TSTACK_H_
