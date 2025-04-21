// Copyright 2021 NNTU-CS
#include <string>
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int SIZE>
class TStack {
 private:
    T arr[SIZE];
    int top;

 public:
    TStack() : top(-1) {}
    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == SIZE - 1; }
    void push(const T& value) {
      if (!isFull()) {
        arr[++top] = value;
      } else {
        throw std::string("Full");
      }
    }
    void pop(T& value) {
      if (!isEmpty()) {
        value = arr[top--];
      } else {
        throw std::string("Empty");
      }
    }
    T get() const {
      if (!isEmpty()) {
        return arr[top];
      } else {
        throw std::string("Empty");
      }
    }
};

#endif  // INCLUDE_TSTACK_H_
