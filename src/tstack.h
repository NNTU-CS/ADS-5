// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <iostream>

template<typename T, int size>
class TStack{
private:
    T stack[size];
    int top;

public:
    TStack() : top(-1) {}
    void push(const T& value) {
        if (top < size - 1) {
            stack[++top] = value;
        } else {
            // stack is full
            throw std::out_of_range("Stack is full");
        }
    }

    T pop() {
        if (top >= 0) {
            return stack[top--];
        } else {
            // stack is empty
            throw std::out_of_range("Stack is empty");
        }
    }

    T peek() const {
        if (top >= 0) {
            return stack[top];
        } else {
            // stack is empty
            throw std::out_of_range("Stack is empty");
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
