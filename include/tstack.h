// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T* ptr;
    int x;

 public:
    TStack() : x(0) {
        ptr = new T[size];
    }
    void pushup(const T& c) {
        if (size - 1 >= x) {
            ptr[x++] = c;
        } else {
            throw std::string("Fall !");
        }
    }
    T popback() {
        if (x > 0) {
            return ptr[--x];
        } else {
            throw std::string("Empty");
        }
    }
    bool IfZero() const {
        return x == 0;
    }
    T ElemUp() const {
        if (x > 0) {
            return ptr[x - 1];
        } else {
            throw std::string("Fall!");
        }
    }
};

#endif  // INCLUDE_TSTACK_H_
