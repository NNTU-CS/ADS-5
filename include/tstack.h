// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template<typename T, int kSize>
class TStack {
 private:
  T data[kSize];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  bool isEmpty() const {
    return topIndex == -1;
  }

  bool isFull() const {
    return topIndex == kSize - 1;
  }

  void push(const T& value) {
    if (isFull()) {
      throw std::overflow_error("Stack overflow");
    }
    data[++topIndex] = value;
  }

  T pop() {
    if (isEmpty()) {
      throw std::underflow_error("Stack underflow");
    }
    return data[topIndex--];
  }

  T top() const {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return data[topIndex];
  }
};

#endif  // INCLUDE_TSTACK_H_
