// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>
template<typename T, int size>
class TStack {
// добавьте код стека
 private:
    T data[100];
    int top;

 public:
    TStack() : top(-1) {}
    void posh(T value) {
        if (top != size - 1) {
            data[++top] = value;
        } else {
            throw std::string("Full");
        }
    }
    bool empty() {
        return top == -1;
    }
    T got() const {
        return data[top];
    }
    T pop() {
        if (empty()) {
            throw std::string("Empty");
        } else {
        return data[top--];
        }
    }
};
#endif  // INCLUDE_TSTACK_H_
