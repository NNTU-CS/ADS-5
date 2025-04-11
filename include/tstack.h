// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template<typename T, int size>
class TStack {
private:
    T data[SIZE];
    int topIndex;
public:
    TStack() : topIndex(-1) {}
    void push(const T& value) {
        if (topIndex >= SIZE - 1) {
            throw std::overflow_error("Стек переполнен");
        }
        data[++topIndex] = value;
    }
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Стек неполный");
        }
        return data[topIndex--];
    }
    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Стек пуст");
        }
        return data[topIndex];
    }
    bool isEmpty() const {
        return topIndex == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
