// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <string>

template<typename T, int size>
class TStack {
 private:
    T StData[100];
    int top;

 public:
    TStack() : top(-1) {}
    void push(T value) {
        if (!full())
            StData[++top] = value;
        else
            throw std::string("Is-Full");
    }
    T get() {
        return StData[top];
    }
    T pop() {
        if (IsEmptyy()) {
            throw std::string("Is-Empty");
        } else {
            return StData[top--];
        }
    }
    bool IsEmptyy() {
        return top == -1;
    }
    bool full() {
        return top == size - 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
