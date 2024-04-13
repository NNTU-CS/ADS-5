// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <iostream>

template<typename T, int size>
class TStack {
 private:
    T* arr;
    int top;

 public:
    TStack() {
        arr = new T[size];
        top = -1;
    }
    ~TStack() { delete[] arr; }
    void push(T val) {
        if (top == size - 1) {
            std::cout << "Stack overflow" << std::endl;
            return;
        }
        arr[++top] = val;
    }
    T pop() {
        if (top == -1) {
            std::cout << "Stack is empty" << std::endl;
            return T();
        }
        return arr[top--];
    }
    T getTop() {
        if (top == -1) {
            std::cout << "Stack is empty" << std::endl;
            return T();
        }
        return arr[top];
    }
    bool isEmpty() { return top == -1; }
};
#endif  // INCLUDE_TSTACK_H_
