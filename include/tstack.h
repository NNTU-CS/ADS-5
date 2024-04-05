// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
 private:
    T*data;
    int top;

 public:
    TStack() :top(0) {
     data = new T[size];
    }
    void push(const T& item) {
        if (top <= size - 1) {
            data[top++] = item;
        } else {
            throw std::string("full");
        }
    }
    T pop() {
        if (top > 0) {
            return data[--top];
        } else {
            throw std::string("Empty");
        }
    }
    bool isEmpty()const {
        return top == 0;
    }
    T get() const {
        if (top > 0) {
            return data[top - 1];
        } else {
            throw std::string("Empty");
        }
    }
};

#endif  // INCLUDE_TSTACK_H_
