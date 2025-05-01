// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template<typename T, int size>
class TStack {
 private:
  static constexpr int kStaticSize = size;
  T mas[kStaticSize];
  int top;

 public:
  TStack() : top(-1) {}
  bool isEmpty() const { return top == -1; }
  bool isFull() const { return top == size - 1; }
  void push(T val) {
    if (isFull()) {
      throw std::overflow_error("Stack is full");
    }
    mas[++top] = val;
  }
  T pop() {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return mas[top--];
  }
  T getTop() const {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return mas[top];
  }
};

#endif  // INCLUDE_TSTACK_H_
