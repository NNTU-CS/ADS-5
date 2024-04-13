// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <iostream>

template<typename T, int size>
class TStack{
private:
    T * data;
    int top = 0;

public:
    TStack() : top(-1) {
        data = new T[size];
    }
    ~TStack() {
        delete[] data;
    }
    void push(const T& value) {
        if (!isFull()) {
            data[++top] = value;
        } else {
            throw std::overflow_error("Stack is full");
        }
    }
    T stTop() {
    if (top > 0) {
        return data[top - 1];
    } else {
        return -1;
    }
    }
    T pop() {
    if (top == 0) {
        throw std::string("Empty!!");
    } else {
      top--;
      return data[top];
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
