// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <iostream>

template<typename T, int size>
class TStack {
 private:
    T* array;
    int top;

 public:
    TStack() : top(0) {
        array = new T[size];
    }

    T pop() {
        if (top == 0) {
            throw "Empty!";
        } else {
            top -= 1;
            return array[top];
        }
    }

    void push(T item) {
        array[top] = item;
        top++;
    }

    T get() const {
        return array[top];
    }

    bool isempty() {
        return top == 0;
    }

    T check() {
        if (top == 0) {
            throw "Empty!";
        } else {
            return array[top - 1];
        }
    }
};

#endif  // INCLUDE_TSTACK_H_
