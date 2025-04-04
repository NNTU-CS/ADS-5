// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template<typename T, int size>
class TStack {
  private:
    T arr[size];
    int top;
public:
    TStack() : top(-1) {}
    void push(T value) {
        if (top >= size - 1) {
            throw std::overflow_error("Stack is full");
        }
        arr[++top] = value;
    }
    T pop() {
        if (top < 0) {
            throw std::underflow_error("Stack is empty");
        }
        return arr[top--];
    }
    T peek() const { 
        if (top < 0) {
            throw std::underflow_error("Stack is empty");
        }
        return arr[top];
    }
    bool isEmpty() const {
        return top < 0;
    }
};
#endif  // INCLUDE_TSTACK_H_
