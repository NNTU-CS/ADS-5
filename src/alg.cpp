// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template <typename T, int Size>
class TStack {
private:
    T arr[Size];
    int top;
public:
    TStack() : top(-1) {}
    void push(const T& val) {
        if (isFull()) {
            throw std::overflow_error("Stack is full");
        }
        arr[++top] = val;
    }
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return arr[top--];
    }
    const T& peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return arr[top];
    }
    bool isEmpty() const {
        return top == -1;
    }
    bool isFull() const {
        return top == Size - 1;
    }
    int size() const {
        return top + 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
