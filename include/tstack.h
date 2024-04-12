// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
 private:
    static const int kSize = size;
    T data[kSize];
    int top;

 public:
    TStack() : top(0) {}
    T get() const {
        if (!isEmpty())
            return data[top-1];
        else
            throw std::string("Empty");
    }
    bool isEmpty() const {
        return top == 0;
    }
    T pop() {
        if (top > 0)
            return data[--top];
        else
            throw std::string("End");
    }
    void push(T item) {
        if (top <= size - 1)
            data[top++] = item;
        else
            throw std::string("Full");
    }
};

#endif  // INCLUDE_TSTACK_H_
