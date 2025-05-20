// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

template<typename T, int size>
class TStack {
 public:
  TStack() : top(-1) {}

  bool IsFull() const {
    return top == size - 1;
  }

  bool IsEmpty() const {
    return top == -1;
  }

  void Push(const T& value) {
    if (IsFull()) {
      throw std::overflow_error("Stack overflow");
    }
    data[++top] = value;
  }

  T Pop() {
    if (IsEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return data[top--];
  }

  T Top() const {
    if (IsEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return data[top];
  }

  int Size() const {
    return top + 1;
  }

 private:
  int top;
  T data[size];
};

#endif  // INCLUDE_TSTACK_H_
