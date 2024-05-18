// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <string>

template <typename T, const int CAPACITY>
class TStack {
 private:
    T arr[CAPACITY];
    int top;

 public:
    TStack() : top(-1) {}

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return size() == CAPACITY; }

    T get() const { return isEmpty() ? throw std::string("empty") : arr[top]; }
    T pop() { return isEmpty() ? throw std::string("empty") : arr[top--]; }
    void push(T v) { isFull() ? throw std::string("full") : arr[++top] = v; }

    int size() const { return top + 1; }
};

#endif  // INCLUDE_TSTACK_H_
