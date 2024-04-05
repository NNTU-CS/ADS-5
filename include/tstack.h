// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <string>
template<typename T, int size>
class TStack {
 private:
    T data[100];
    int top_index;

 public:
    TStack() : top_index(-1) {}
    void push(T value) {
       if (top_index != size - 1) {
           data[++top_index] = value;
       } else {
           throw std::string("Stack is full");
       }
    }

    T get() const {
        return data[top_index];
    }
    T pop() {
        if (isEmpty()) {
            throw std::string("Stack is empty");
        } else {
            return data[top_index--];
        }
    }

    bool isEmpty() {
        return top_index == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
