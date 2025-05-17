// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <iostream>

template<typename T, int kStackSize>
class TStack {
 private:
  T data[kStackSize];
  int topIndex;
 public:
  TStack() : topIndex(-1) {}
  bool isEmpty() const {
    return topIndex == -1;
  }
  bool isFull() const {
    return topIndex == kStackSize - 1;
  }
  void push(const T& element) {
    if (isFull()) {
      std::cerr << "Stack Overflow!" << std::endl;
      return;
    }
    data[++topIndex] = element;
  }
  T pop() {
    if (isEmpty()) {
      std::cerr << "Stack Underflow!" << std::endl;
      return T();
    }
    return data[topIndex--];
  }
  T top() const {
    if (isEmpty()) {
      std::cerr << "Stack is Empty!" << std::endl;
      return T();
    }
    return data[topIndex];
  }
  int get_size() const {
    return kStackSize;
  }
};

#endif  // INCLUDE_TSTACK_H_
