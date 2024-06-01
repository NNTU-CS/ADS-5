// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#pragma once
#include <iostream>

template<typename T, int size>
class TStack {
 private:
    T* arr = NULL;
    int current;

 public:
    void push(T info) {
        if (size == current) {
            std::cout << "Переполнение стека" << std::endl;
        } else if (arr == NULL) {
            arr = new T[size];
            current = 0;
            arr[current++] = info;
        } else {
            arr[current++] = info;
        }
    }
    bool isEmpty() {
        if (current == 0) {
            return true;
        } else {
            return false;
        }
    }
    T top() {
        if (isEmpty()) {
            return 0;
        } else {
            return arr[current - 1];
        }
    }
    T pop() {
        if (isEmpty()) {
            return 0;
        } else {
            return arr[--current];
        }
    }
};
#endif  // INCLUDE_TSTACK_H_
