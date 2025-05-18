// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template<typename T, int MaxSize>
class TStack {
public:
    TStack() : topIndex(-1) {}

    bool empty() const {
        return topIndex == -1;
    }

    bool full() const {
        return topIndex == MaxSize - 1;
    }

    void push(const T& value) {
        if (full()) {
            throw std::overflow_error("Stack overflow");
        }
        storage[++topIndex] = value;
    }

    T pop() {
        if (empty()) {
            throw std::underflow_error("Stack underflow");
        }
        return storage[topIndex--];
    }

    T peek() const {
        if (empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return storage[topIndex];
    }

private:
    T storage[MaxSize];
    int topIndex;
};

#endif  // INCLUDE_TSTACK_H_
