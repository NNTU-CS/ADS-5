// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <iostream>
#include <stdexcept>

template<typename T, int size>
class TStack {
 private :
    T* data;
    int top;

 public :
    TStack() : top(-1) {
        data = new T[size];
    }

    ~TStack() {
        delete[] data;
    }

    void push(T value) {
        if (top == size - 1) {
            throw std::overflow_error("Stack overflow");
        }
        data[++top] = value;
    }

    T pop() {
        if (top == -1) {
            throw std::underflow_error("Stack underflow");
        }
        return data[top--];
    }

    T watch() {
        if (top < 0) {
            throw std::underflow_error("Stack underflow");
        }
        return data[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
