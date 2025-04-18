// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

constexpr int k = 100;

template <typename T, int size = k>
class TStack {
 private:
  T data[size];
  int top;

 public:
  TStack() : top(-1) {}

  void push(const T& val) {
    if (top >= size - 1) throw std::overflow_error("Stack overflow");
    data[++top] = val;
  }

  T pop() {
    if (top < 0) throw std::underflow_error("Stack underflow");
    return data[top--];
  }

  T peek() const {
    if (top < 0) throw std::underflow_error("Stack is empty");
    return data[top];
  }

  bool isEmpty() const { return top == -1; }

  bool isFull() const { return top == size - 1; }
};

#endif  // INCLUDE_TSTACK_H_
