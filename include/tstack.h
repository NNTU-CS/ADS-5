// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <string>
#include <stdexcept>

template <typename T, int size>
class TStack {
 private:
    T* data;
    int top;

 public:
    TStack() : top(-1) {
        data = new T[size];
    }
    ~TStack() {
        delete[] data;
    }
    void push(T value) {
        if (!isFull()) {
            data[++top] = value;
        } else {
            throw std::overflow_error("Stack is full");
        }
    }
    T get() const {
         return data[top];
    }
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[top--];
    }
    bool isEmpty() const {
        return top == -1;
    }
    bool isFull() const {
        return top == size - 1;
    }
};

#endif // INCLUDE_TSTACK_H_
