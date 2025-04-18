// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>
template<typename T, int K>
class TStack {
 private:
    T data[K];
    int topInd;

 public:
    TStack() : topInd(-1) {}
    bool isEmpty() const {
        return topInd < 0;
    }
    bool isFull() const {
        return topInd >= K - 1;
    }
    void push(const T& item) {
        if (isFull()) {
            throw std::runtime_error("Full");
        }
        data[++topInd] = item;
    }
    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("Empty");
        }
        --topInd;
    }
    T& top() {
        if (isEmpty()) {
            throw std::runtime_error("Empty");
    }
        return data[topInd];
    }
    const T& top() const {
        if (isEmpty()) {
            throw std::runtime_error("Empty");
        }
        return data[topInd];
    }
};
#endif  // INCLUDE_TSTACK_H_
