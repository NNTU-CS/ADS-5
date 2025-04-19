// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template<typename T, int kCapacity>
class TStack {
 private:
    T stackData[kCapacity];
    int currentIndex;

 public:
    TStack() : currentIndex(-1) {}

    bool isEmpty() const {
        return currentIndex == -1;
    }

    bool isFull() const {
        return currentIndex == kCapacity - 1;
    }

    void push(const T& value) {
        if (isFull()) {
            throw std::overflow_error("Stack overflow: push to full stack");
        }
        stackData[++currentIndex] = value;
    }

    void pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack underflow: pop from empty stack");
        }
        --currentIndex;
    }

    const T& top() const {
        if (isEmpty()) {
            throw std::runtime_error("Accessing top of empty stack");
        }
        return stackData[currentIndex];
    }

    T& top() {
        if (isEmpty()) {
            throw std::runtime_error("Accessing top of empty stack");
        }
        return stackData[currentIndex];
    }
};

#endif  // INCLUDE_TSTACK_H_
