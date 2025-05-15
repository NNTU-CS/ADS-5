// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template<typename T, int size>
class TStack {
 private:
  T data[size];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  bool is_empty() const {
    return topIndex == -1;
  }

  bool is_full() const {
    return topIndex == size - 1;
  }

  void push(const T& value) {
    if (!is_full()) {
      data[++topIndex] = value;
    } else {
      throw std::overflow_error("Stack is full");
    }
  }

  T pop() {
    if (!is_empty()) {
      return data[topIndex--];
    } else {
      throw std::underflow_error("Stack is empty");
    }
  }

  T& top() {
    if (!is_empty()) {
      return data[topIndex];
    } else {
      throw std::underflow_error("Stack is empty");
    }
  }
};

#endif  // INCLUDE_TSTACK_H_
