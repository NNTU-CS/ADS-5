// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>
template<typename T, int K>
class TStack {
 private:
    T data[K];
    int top;

 public:
    TStack() : top(-1) {}
    bool isEmpty() const {
        return top < 0;
    }
    bool isFull() const {
        return top >= K - 1;
    }
    void push(const T& item) {
        if (isFull()) {
            throw std::runtime_error("Full");
        }
        data[++top] = item;
    }
    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("Empty");
        }
        --top;
    }
    T& top() {
        if (isEmpty()) {
            throw std::runtime_error("Empty");
    }
        return data[top];
    }
    const T& top() const {
        if (isEmpty()) {
            throw std::runtime_error("Empty");
        }
        return data[top];
    }
};
#endif  // INCLUDE_TSTACK_H_
