// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>
template<typename T, const int size>
class TStack {
    T data[100];
    int Top;

public:
    TStack() {
        Top = 0;
    }
    void PUSH(const T& item) {
        if (Top <= size - 1)
            data[Top++] = item;
        else
            throw std::string("Full!");
    }
    T POP() {
        if (Top > 0)
            return data[--Top];
        else
            throw std::string("Empty!");
    }
    T ViewTop() {
        if (Top > 0)
            return data[Top - 1];
        else
            return -1;
    }
};
#endif  // INCLUDE_TSTACK_H_
