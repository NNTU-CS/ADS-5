// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>
#include <iostream>

template <typename T, int kStackSize>
class TStack {
private: 
  T stackArray[kStackSize];
  int topIndex;

public: 
  TStack() : topIndex(-1) {}
  void push(const T& value) {
    if (topIndex >= kStackSize - 1) {
      throw std::overflow_error("Stack overflow");
    }
    stackArray[++topIndex] = value;
  }
  T pop() {
    if (isEmpty()) {
      throw std::underflow_error("Stack underflow");
    }
    return stackArray[topIndex--];
  }
  T top() const {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return stackArray[topIndex];
  }
  bool isEmpty() const {
    return topIndex == -1;
  }
};

#endif // INCLUDE_TSTACK_H_
