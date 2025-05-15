// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template<typename T, int kStackSize>
class TStack {
 private:
  T data[kStackSize];
  int top;

 public:
  TStack() : top(-1) {}

  bool is_empty() const {
    return top == -1;
  }

  bool is_full() const {
    return top == kStackSize - 1;
  }

  void push(const T& value) {
    if (!is_full()) {
      data[++top] = value;
    } else {
      throw std::overflow_error("Stack is full");
    }
  }

  T pop() {
    if (!is_empty()) {
      return data[top--];
    } else {
      throw std::underflow_error("Stack is empty");
    }
  }

  T& top() {
    if (!is_empty()) {
      return data[top];
    } else {
      throw std::underflow_error("Stack is empty");
    }
  }
};

#endif  // INCLUDE_TSTACK_H_


