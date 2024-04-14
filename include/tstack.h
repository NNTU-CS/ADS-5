// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>
template<typename T, int size>
class TStack {
 private:
    T* arr;
    int top;

 public:
    TStack() { top = -1; arr = new T[size]; }
    void push(T value) {
        if (isFull())
            throw std::string("string is full");
        else
            arr[++top] = value;
    }
    bool isFull() const {
        return top == size - 1;
    }
    bool isEmpty() const {
        return top == -1;
    }
    const T& Get() {
        if (isEmpty())
            throw std::string("string is empty");
        else
            return arr[top];
    }
    const T& Pop() {
        if (isEmpty())
            throw std::string("string is empty");
        else
            return arr[top--];
    }
};


#endif  // INCLUDE_TSTACK_H_
