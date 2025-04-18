// Copyright 2025 NNTU-CS
#ifndef MODIFIED_STACK_HEADER
#define MODIFIED_STACK_HEADER
#include <stdexcept>

template<typename T, int S>
class TStack {
 private:
    T stackElements[S];
    int currentPosition;

 public:
    TStack() : currentPosition(-1) {}

    void removeLast() {
        if (isEmpty()) {
            throw std::runtime_error("Container underflow");
        }
        --currentPosition;
    }

    void insertElement(const T& newItem) {
        if (isComplete()) {
            throw std::runtime_error("Container overflow");
        }
        stackElements[++currentPosition] = newItem;
    }

    bool isComplete() const {
        return currentPosition >= S - 1;
    }

    bool isEmpty() const {
        return currentPosition < 0;
    }

    const T& peekTop() const {
        if (isEmpty()) {
            throw std::runtime_error("No elements inside");
        }
        return stackElements[currentPosition];
    }

    T& accessTop() {
        if (isEmpty()) {
            throw std::runtime_error("No elements inside");
        }
        return stackElements[currentPosition];
    }
};
#endif
// INCLUDE_TSTACK_H_
