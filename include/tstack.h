// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <string>
#include <stdexcept>

template<typename T, int size>
class TStack {
 private:
    T* elements;
    int stackTop;

 public:
    TStack() : stackTop(-1) {
        elements = new T[size];
    }
    ~TStack() {
        delete[] elements;
    }
    void push(T value) {
        if (!isFull()) {
            elements[++stackTop] = value;
        } else {
            throw std::overflow_error("Stack is full");
        }
    }
    T get() const {
        return elements[stackTop];
    }
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return elements[stackTop--];
    }
    bool isEmpty() const {
        return stackTop == -1;
    }
    bool isFull() const {
        return stackTop == size - 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
