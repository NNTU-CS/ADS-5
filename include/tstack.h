// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template<typename T, int kStackSize>
class TStack {
 private:
  T data[kStackSize];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  bool is_empty() const {
    return topIndex == -1;
  }

  bool is_full() const {
    return topIndex == kStackSize - 1;
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
