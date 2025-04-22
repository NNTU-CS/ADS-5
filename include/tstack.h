// Copyright 2021 NNTU-CS
#include <iostream>
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T data[size];
    int topIndex;  // индекс вершины стека
    
 public:
    TStack() : topIndex(-1) {}  // инициализация пустого стека

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == size - 1;
    }

    void push(const T& value) {
        if (isFull()) {
            throw std::overflow_error("Stack is full");
        }
        data[++topIndex] = value;
    }

    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex--];
    }

    T top() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex];
    }
};

#endif  // INCLUDE_TSTACK_H_