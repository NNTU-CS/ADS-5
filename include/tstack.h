// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template <typename T, int SIZE>
class TStack {
 private:
  T data[SIZE];
  int top;

 public:
  TStack() : top(-1) {}
  void push(const T& value) {
    if (top >= SIZE - 1) {
      throw "Stack overflow";
    }
    data[++top] = value;
  }
  void pop() {
    if (isEmpty()) {
      throw "Stack underflow";
    }
    --top;
  }
  T get() const {
    if (isEmpty()) {
      throw "Stack is empty";
    }
    return data[top];
  }
  bool isEmpty() const {
    return top == -1;
  }
};
#endif
