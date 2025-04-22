// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template <typename T, int size>
class TStack {
 private:
  T data[size];
  int topIndex = -1;

 public:
  bool empty() const {
    return topIndex == -1;
  }

  void push(const T& value) {
    if (topIndex < size - 1) {
      data[++topIndex] = value;
    } else {
      throw std::overflow_error("Stack overflow");
    }
  }

  void pop() {
    if (!empty()) {
      --topIndex;
    } else {
      throw std::underflow_error("Stack underflow");
    }
  }

  T top() const {
    if (!empty()) {
      return data[topIndex];
    } else {
      throw std::underflow_error("Stack is empty");
    }
  }

  int sizeOfStack() const {
    return topIndex + 1;
  }
};

#endif  // INCLUDE_TSTACK_H_
